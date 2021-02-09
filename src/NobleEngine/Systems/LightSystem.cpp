#include "LightSystem.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"
#include "../EngineCore/ResourceManager.h"

namespace NobleEngine
{
	SetupComponentList(Light);

	void LightSystem::PreRender()
	{
		for (size_t sha = 0; sha < ResourceManager::shaderPrograms.size(); sha++)
		{
			if (ResourceManager::shaderPrograms.at(sha))
			{
				ResourceManager::shaderPrograms.at(sha)->UseProgram();

				ResourceManager::shaderPrograms.at(sha)->BindVector3("u_ViewPos", Application::activeCam->camTransform->position);
				ResourceManager::shaderPrograms.at(sha)->BindVector3("u_AmbientLight", glm::vec3(1.0f, 1.0f, 1.0f));
				ResourceManager::shaderPrograms.at(sha)->BindFloat("u_AmbientLightStrength", 0.1f);

				ResourceManager::shaderPrograms.at(sha)->BindVector3("lights.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
				ResourceManager::shaderPrograms.at(sha)->BindVector3("lights.position", glm::vec3(0, 5, 0));
				ResourceManager::shaderPrograms.at(sha)->BindVector3("lights.diffuseLight", glm::vec3(1.0, 0.0, 0.0));
				ResourceManager::shaderPrograms.at(sha)->BindVector3("lights.specularLight", glm::vec3(1.0, 0.0, 0.0));
				ResourceManager::shaderPrograms.at(sha)->BindFloat("lights.constant", 1.0f);
				ResourceManager::shaderPrograms.at(sha)->BindFloat("lights.linear", 0.09f);
				ResourceManager::shaderPrograms.at(sha)->BindFloat("lights.quadratic", 0.032f);
				ResourceManager::shaderPrograms.at(sha)->BindFloat("lights.intensity", 1.0f);

				glUseProgram(0);
			}
		}
	}

	void LightSystem::OnRender(std::shared_ptr<Light> comp)
	{

	}
}