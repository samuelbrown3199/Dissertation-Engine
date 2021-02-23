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

				for (int i = 0; i < Light::componentList.size(); i++)
				{
					std::string location = "lights[" + std::to_string(i);

					ResourceManager::shaderPrograms.at(sha)->BindVector3(location + "].direction", Light::componentList.at(i)->lightTransform->rotation);
					ResourceManager::shaderPrograms.at(sha)->BindVector3(location + "].position", Light::componentList.at(i)->lightTransform->position);

					switch (Light::componentList.at(i)->type)
					{
					case Light::LightType::Directional:
						ResourceManager::shaderPrograms.at(sha)->BindInt(location + "].lightType", 0);
						break;
					case Light::LightType::Point:
						ResourceManager::shaderPrograms.at(sha)->BindInt(location + "].lightType", 1);
						break;
					}

					ResourceManager::shaderPrograms.at(sha)->BindVector3(location + "].diffuseLight", Light::componentList.at(i)->diffuseColour);
					ResourceManager::shaderPrograms.at(sha)->BindVector3(location + "].specularLight", Light::componentList.at(i)->specularColour);
					ResourceManager::shaderPrograms.at(sha)->BindFloat(location + "].constant", Light::componentList.at(i)->constant);
					ResourceManager::shaderPrograms.at(sha)->BindFloat(location + "].linear", Light::componentList.at(i)->linear);
					ResourceManager::shaderPrograms.at(sha)->BindFloat(location + "].quadratic", Light::componentList.at(i)->quadratic);
					ResourceManager::shaderPrograms.at(sha)->BindFloat(location + "].intensity", Light::componentList.at(i)->intensity);
				}

				glUseProgram(0);
			}
		}
	}

	void LightSystem::OnRender(std::shared_ptr<Light> comp)
	{

	}
}