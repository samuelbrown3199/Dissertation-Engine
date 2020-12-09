#include "TransformSystem.h"

namespace NobleEngine
{
	SetupComponentList(Transform);

	void TransformSystem::Update()
	{
		for (size_t tr = 0; tr < Transform::componentList.size(); tr++)
		{
			GenerateModelMatrix(Transform::componentList.at(tr));
		}
	}

	void TransformSystem::GenerateModelMatrix(std::shared_ptr<Transform> tr)
	{
		tr->model = glm::mat4(1.0f);

		tr->model = glm::translate(tr->model, tr->position);
		tr->model = glm::rotate(tr->model, glm::radians(tr->rotation.x), glm::vec3(1, 0, 0));
		tr->model = glm::rotate(tr->model, glm::radians(tr->rotation.y), glm::vec3(0, 1, 0));
		tr->model = glm::rotate(tr->model, glm::radians(tr->rotation.z), glm::vec3(0, 0, 1));
		tr->model = glm::scale(tr->model, tr->scale);
	}
}