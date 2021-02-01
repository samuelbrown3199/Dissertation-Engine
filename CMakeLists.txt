cmake_minimum_required(VERSION 2.6)
project(Noble)

include_directories(
	src
)

if(MSVC)

	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MT")

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
  src/NobleEngine/EngineCore/Application.h
  src/NobleEngine/EngineCore/Application.cpp
  src/NobleEngine/EngineCore/Screen.h
  src/NobleEngine/EngineCore/Screen.cpp
  src/NobleEngine/EngineCore/ThreadingManager.h
  src/NobleEngine/EngineCore/ThreadingManager.cpp
  src/NobleEngine/EngineCore/ResourceManager.h
  src/NobleEngine/EngineCore/ResourceManager.cpp
  src/NobleEngine/EngineCore/InputManager.h
  src/NobleEngine/EngineCore/InputManager.cpp
  src/NobleEngine/EngineCore/PhysicsWorld.h
  src/NobleEngine/EngineCore/PhysicsWorld.cpp

  src/NobleEngine/EngineCore/Resource.h
  src/NobleEngine/ResourceManagement/Texture.h
  src/NobleEngine/ResourceManagement/Texture.cpp
  src/NobleEngine/ResourceManagement/AudioClip.h
  src/NobleEngine/ResourceManagement/AudioClip.cpp
  src/NobleEngine/ResourceManagement/Model.h
  src/NobleEngine/ResourceManagement/Material.h
  src/NobleEngine/ResourceManagement/Shader.h
  src/NobleEngine/ResourceManagement/ShaderProgram.h
  src/NobleEngine/ResourceManagement/ShaderProgram.cpp
  src/NobleEngine/ResourceManagement/SpriteSheet.h
  src/NobleEngine/ResourceManagement/SpriteSheet.cpp

  src/NobleEngine/EngineCore/Entity.h
  src/NobleEngine/EngineCore/Entity.cpp
  src/NobleEngine/EngineCore/Component.h
  src/NobleEngine/EngineCore/System.h

  src/NobleEngine/Components/Transform.h
  src/NobleEngine/Systems/TransformSystem.h
  src/NobleEngine/Systems/TransformSystem.cpp

  src/NobleEngine/Components/MeshRenderer.h
  src/NobleEngine/Systems/MeshRendererSystem.h
  src/NobleEngine/Systems/MeshRendererSystem.cpp

  src/NobleEngine/Components/Camera.h
  src/NobleEngine/Systems/CameraSystem.h
  src/NobleEngine/Systems/CameraSystem.cpp

  src/NobleEngine/Components/PhysicsBody.h
  src/NobleEngine/Systems/PhysicsBodySystem.h
  src/NobleEngine/Systems/PhysicsBodySystem.cpp

  src/NobleEngine/Components/AudioSource.h
  src/NobleEngine/Systems/AudioSourceSystem.h
  src/NobleEngine/Systems/AudioSourceSystem.cpp

  src/NobleEngine/Components/AudioListener.h
  src/NobleEngine/Systems/AudioListenerSystem.h
  src/NobleEngine/Systems/AudioListenerSystem.cpp

  src/NobleEngine/Components/Light.h
  src/NobleEngine/Systems/LightSystem.h
  src/NobleEngine/Systems/LightSystem.cpp

  src/NobleEngine/Components/SpriteRenderer.h
  src/NobleEngine/Systems/SpriteRendererSystem.h
  src/NobleEngine/Systems/SpriteRendererSystem.cpp
)
target_link_libraries(NobleEngine SDL2 SDL2_ttf glew32 opengl32 openal32 Bullet3Collision Bullet3Common Bullet3Dynamics Bullet3Geometry BulletCollision BulletDynamics LinearMath)

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