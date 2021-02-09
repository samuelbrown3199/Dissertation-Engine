#include "RotatorSystem.h"

SetupComponentList(Rotator);

void RotatorSystem::OnUpdate(std::shared_ptr<Rotator> comp)
{
	comp->transform->rotation.x += comp->rotationRate;
	std::cout << comp->transform->rotation.x << std::endl;
}