#include "Scene.h"

namespace NobleEngine
{
	DirectionalLight::DirectionalLight()
	{
		diffuseLightColour = glm::vec3(1.0f, 1.0f, 1.0f);
		specularLightColour = glm::vec3(1.0f, 1.0f, 1.0f);
		direction = glm::vec3(0.0f, -90.0f, 0.0f);

		intensity = 1.0f;
	}

	Environment::Environment()
	{
		ambientLightColour = glm::vec3(1.0f, 1.0f, 1.0f);
		ambientLightStrength = 0.1f;

		directionalLight = std::make_shared<DirectionalLight>();
	}


	Scene::Scene()
	{
		sceneEnvironment = std::make_shared<Environment>();
	}
	std::shared_ptr<Entity> Scene::CreateEntity()
	{
		std::shared_ptr<Entity> en = std::make_shared<Entity>();
		en->entityID = sceneEntities.size();
		en->self = en;
		sceneEntities.push_back(en);
		return en;
	}
}