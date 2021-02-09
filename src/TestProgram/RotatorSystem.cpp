#include "RotatorSystem.h"

SetupComponentList(Rotator);

void RotatorSystem::OnUpdate(std::shared_ptr<Rotator> comp)
{
	comp->transform->rotation.z += comp->rotationRate;
}