#pragma once
#ifndef FLYINGCAM_H_
#define FLYINGCAM_H_


#include <NobleEngine/EngineCore/Component.h>

#include <glm/glm.hpp>

using namespace NobleEngine;
struct FlyingCam : public Component<FlyingCam>
{
	bool firstMouse = true;
	float pitch = 0.0f, yaw = -90.0f;

	const float movementSpeed = 2.5f;
	glm::vec2 oldMousePos, newMousePos;
};

#endif