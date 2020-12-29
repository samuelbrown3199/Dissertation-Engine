#include "CameraSystem.h"

#include "Application.h"
#include "Entity.h"
#include "Transform.h"

#include<glm/glm.hpp>
#include<glm/ext.hpp>

namespace NobleEngine
{
	SetupComponentList(Camera);

	void CameraSystem::OnUpdate(std::shared_ptr<Camera> comp)
	{
		UpdateCameraView(comp);
	}

	void CameraSystem::UpdateCameraView(std::shared_ptr<Camera> cam)
	{
		std::shared_ptr<Transform> camTransform = GetApplication()->GetEntity(cam->entityID)->GetComponent<Transform>();
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		cam->viewMatrix = glm::lookAt(camTransform->position, camTransform->position + cam->forward, up);
	}
}