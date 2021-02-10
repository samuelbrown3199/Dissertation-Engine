#pragma once
#ifndef ROTATORSYSTEM_H_
#define ROTATORSYSTEM_H_

#include <NobleEngine/EngineCore/System.h>

#include "Rotator.h"

using namespace NobleEngine;
struct RotatorSystem : public System<Rotator>
{
	void OnUpdate(std::shared_ptr<Rotator> comp);
};

#endif