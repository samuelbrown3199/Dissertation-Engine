#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "../EngineCore/Entity.h"
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
		*Determines whether this is the engines main camera.
		*/
		bool mainCamera = false;
		/**
		*Stores the cameras entity transform component.
		*/
		std::shared_ptr<Transform> camTransform;
		/**
		*Stores the cameras view matrix.
		*/
		glm::mat4 viewMatrix;

		/**
		*Used to initialize a camera component. Parameter mainCam is used to detemine whether this is the active cam that the engine will use in rendering.
		*/
		void OnInitialize(bool mainCam)
		{
			camTransform = GetEntity()->GetComponent<Transform>();

			if (camTransform->rotation == glm::vec3(0, 0, 0))
			{
				camTransform->rotation = glm::vec3(0, 0, -1.0f);
			}

			mainCamera = mainCam;
		}
	};
}

#endif