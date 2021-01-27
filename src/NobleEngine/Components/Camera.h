#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "../EngineCore/Component.h"
#include "../Components/Transform.h"

#include "glm/glm.hpp"

namespace NobleEngine
{
	/**
	*Camera Component. Attach to an object to view from the scene from that objects transform.
	*/
	struct Camera : public Component<Camera>
	{
		/**
		*Stores the cameras entity transform component.
		*/
		std::shared_ptr<Transform> camTransform;
		/**
		*Stores the cameras view matrix.
		*/
		glm::mat4 viewMatrix;
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	};
}

#endif