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
  src/NobleEngine/EngineCore.h
  src/NobleEngine/Application.h
  src/NobleEngine/Application.cpp
  src/NobleEngine/Screen.h
  src/NobleEngine/Screen.cpp
  src/NobleEngine/ResourceManager.h
  src/NobleEngine/ResourceManager.cpp
  src/NobleEngine/InputManager.h
  src/NobleEngine/InputManager.cpp
  src/NobleEngine/Resource.h
  src/NobleEngine/Texture.h
  src/NobleEngine/Texture.cpp
  src/NobleEngine/AudioClip.h
  src/NobleEngine/AudioClip.cpp
  src/NobleEngine/Model.h
  src/NobleEngine/Material.h
  src/NobleEngine/Shader.h
  src/NobleEngine/ShaderProgram.h
  src/NobleEngine/ShaderProgram.cpp
  src/NobleEngine/System.h
  src/NobleEngine/Entity.h
  src/NobleEngine/Entity.cpp
  src/NobleEngine/Component.h
  src/NobleEngine/Transform.h
  src/NobleEngine/TransformSystem.h
  src/NobleEngine/TransformSystem.cpp
  src/NobleEngine/MeshRenderer.h
  src/NobleEngine/MeshRendererSystem.h
  src/NobleEngine/MeshRendererSystem.cpp
  src/NobleEngine/Camera.h
  src/NobleEngine/CameraSystem.h
  src/NobleEngine/CameraSystem.cpp
)
target_link_libraries(NobleEngine glew32 opengl32 SDL2 openal32)

add_executable(TestProgram
  src/TestProgram/main.cpp
  src/TestProgram/FlyingCam.h
  src/TestProgram/FlyingCamSystem.h
  src/TestProgram/FlyingCamSystem.cpp
)
target_link_libraries(TestProgram NobleEngine)

add_executable(TechDemo
  src/TechDemo/main.cpp
)