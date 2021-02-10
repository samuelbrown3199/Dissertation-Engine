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

		if (!comp->pBody)
		{
			if (comp->position != comp->oldPosition || comp->rotation != comp->oldRotation || comp->scale != comp->oldScale)
			{
				FixRotation(comp->rotation.x);
				FixRotation(comp->rotation.y);
				FixRotation(comp->rotation.z);

				comp->model = glm::mat4(1.0f);

				comp->model = glm::translate(comp->model, comp->position);
				comp->model = glm::rotate(comp->model, glm::radians(comp->rotation.x), glm::vec3(1, 0, 0));
				comp->model = glm::rotate(comp->model, glm::radians(comp->rotation.y), glm::vec3(0, 1, 0));
				comp->model = glm::rotate(comp->model, glm::radians(comp->rotation.z), glm::vec3(0, 0, 1));
				comp->model = glm::scale(comp->model, comp->scale);

				if (comp->parent)
				{
					comp->model = comp->model * comp->parent->model;
				}

				comp->oldPosition = comp->position;
				comp->oldRotation = comp->rotation;
				comp->oldScale = comp->scale;
			}
		}
		else
		{
			if (comp->pBody->bodyTransform == comp->oldBodyPos)
			{
				return;
			}
			btScalar matrix[16];
			comp->pBody->bodyTransform.getOpenGLMatrix(matrix);
			comp->model = glm::mat4(1.0f);

			comp->model = glm::make_mat4(matrix);
			comp->model = glm::scale(comp->model, comp->scale);

			if (comp->parent)
			{
				comp->model *= comp->parent->model;
			}

			comp->oldBodyPos = comp->pBody->bodyTransform;
		}
	}

	void TransformSystem::FixRotation(float& value)
	{
		if (value > 360)
		{
			value = -360;
		}
		else if (value < -360)
		{
			value = 360;
		}
	}
}