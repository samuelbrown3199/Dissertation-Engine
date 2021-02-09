#pragma once
#ifndef ROTATOR_H_
#define ROTATOR_H_

#include <NobleEngine/EngineCore/Component.h>
#include <NobleEngine/EngineCore/Entity.h>
#include <NobleEngine/Components/Transform.h>

using namespace NobleEngine;
struct Rotator : public Component<Rotator>
{
	std::shared_ptr<Transform> transform;
	float rotationRate = 1.0f;

	void OnInitialize()
	{
		transform = GetEntity()->GetComponent<Transform>();
		rotationRate = 1.0f;
	}
};

#endif