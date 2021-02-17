#include "CameraSystem.h"

#include "../EngineCore/Application.h"
#include "../EngineCore/Entity.h"

#include<glm/glm.hpp>
#include<glm/ext.hpp>

namespace NobleEngine
{
	SetupComponentList(Camera);

	void CameraSystem::OnUpdate(std::shared_ptr<Camera> comp)
	{
		if (!comp->camTransform)
		{
			comp->camTransform = GetApplication()->GetEntity(comp->entityID)->GetComponent<Transform>();
		}
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		comp->viewMatrix = glm::lookAt(comp->camTransform->position, comp->camTransform->position + comp->camTransform->rotation, up);

		if (comp->mainCamera)
		{
			Application::activeCam = comp;
		}
	}
}