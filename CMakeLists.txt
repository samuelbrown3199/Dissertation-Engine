cmake_minimum_required(VERSION 2.6)
project(Noble)

include_directories(
	src
)

if(MSVC)
	include_directories(
		contrib/msvc-windows-x86_64/include
	)
	link_directories(
		${PROJECT_SOURCE_DIR}/contrib/msvc-windows-x86_64/lib
	)
endif()

add_definitions(-DSDL_MAIN_HANDLED)
add_library(NobleEngine
  src/NobleEngine/Application.h
  src/NobleEngine/Application.cpp
)
target_link_libraries(NobleEngine glew32 opengl32 SDL2)

add_executable(TestProgram
  src/TestProgram/main.cpp
)
target_link_libraries(TestProgram NobleEngine)

add_executable(TechDemo
  src/TechDemo/main.cpp
)