#include "TransformSystem.h"
#include "../Components/PhysicsBody.h"

#include <Bullet/btBulletDynamicsCommon.h>

namespace NobleEngine
{
	SetupComponentList(Transform);

	void TransformSystem::OnUpdate(std::shared_ptr<Transform> comp)
	{
		if (!comp->checkForPhysicsBody)
		{
			comp->pBody = GetApplication()->GetEntity(comp->entityID)->GetComponent<PhysicsBody>();
			comp->checkForPhysicsBody = true;
		}
		GenerateModelMatrix(comp);
	}

	void TransformSystem::GenerateModelMatrix(std::shared_ptr<Transform> tr)
	{
		if (!tr->pBody)
		{
			tr->model = glm::mat4(1.0f);

			tr->model = glm::translate(tr->model, tr->position);
			tr->model = glm::rotate(tr->model, glm::radians(tr->rotation.x), glm::vec3(1, 0, 0));
			tr->model = glm::rotate(tr->model, glm::radians(tr->rotation.y), glm::vec3(0, 1, 0));
			tr->model = glm::rotate(tr->model, glm::radians(tr->rotation.z), glm::vec3(0, 0, 1));
			tr->model = glm::scale(tr->model, tr->scale);

			if (tr->parent)
			{
				tr->model = tr->model * tr->parent->model;
			}
		}
		else
		{
			btScalar matrix[16];
			tr->pBody->bodyTransform.getOpenGLMatrix(matrix);
			tr->model = glm::mat4(1.0f);

			tr->model = glm::make_mat4(matrix);
			tr->model = glm::scale(tr->model, tr->scale);

			if (tr->parent)
			{
				tr->model *= tr->parent->model;
			}
		}
	}
}