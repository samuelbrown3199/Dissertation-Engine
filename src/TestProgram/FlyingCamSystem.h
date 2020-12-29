#pragma once
#ifndef FLYINGCAMSYSTEM_H_
#define FLYINGCAMSYSTEM_H_

#include <NobleEngine/System.h>

#include "FlyingCam.h"

using namespace NobleEngine;
struct FlyingCamSystem : public System<FlyingCam>
{
	void OnUpdate(std::shared_ptr<FlyingCam> comp);
	void UpdateControls(std::shared_ptr<FlyingCam> cam);
	void UpdateCameraRotation(std::shared_ptr<FlyingCam> cam);
};

#endif