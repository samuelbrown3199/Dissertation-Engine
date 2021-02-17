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

		void OnInitialize(bool mainCam)
		{
			mainCamera = mainCam;
		}
	};
}

#endif