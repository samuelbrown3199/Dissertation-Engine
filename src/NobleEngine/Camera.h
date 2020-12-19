#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Component.h"

#include "glm/glm.hpp"

namespace NobleEngine
{
	/**
	*Camera Component. Attach to an object to view from the scene from that objects transform.
	*/
	struct Camera : public Component<Camera>
	{
		/**
		*Stores the cameras view matrix.
		*/
		glm::mat4 viewMatrix;
	};
}

#endif