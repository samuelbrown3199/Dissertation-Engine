#include "CameraSystem.h"

#include "Application.h"
#include "Entity.h"
#include "Transform.h"

#include<glm/glm.hpp>
#include<glm/ext.hpp>

namespace NobleEngine
{
	SetupComponentList(Camera);

	void CameraSystem::Update()
	{
		for (size_t ca = 0; ca < Camera::componentList.size(); ca++)
		{
			UpdateCameraView(Camera::componentList.at(ca));
		}
	}

	void CameraSystem::UpdateCameraView(std::shared_ptr<Camera> cam)
	{
		std::shared_ptr<Transform> camTransform = GetApplication()->GetEntity(cam->entityID)->GetComponent<Transform>();
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		cam->viewMatrix = glm::lookAt(camTransform->position, camTransform->position + forward, up);
	}
}