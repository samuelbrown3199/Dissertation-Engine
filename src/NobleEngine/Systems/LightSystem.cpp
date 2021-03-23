#include "LightSystem.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"
#include "../EngineCore/ResourceManager.h"
#include "../EngineCore/Scene.h"

#include <math.h>
#include <algorithm>

namespace NobleEngine
{
	SetupComponentList(Light);

	bool LightSystem::SortByDistance(std::shared_ptr<Light>& light1, std::shared_ptr<Light>& light2)
	{
		return light1->distanceToCamera < light2->distanceToCamera;
	}

	void LightSystem::OnUpdate(std::shared_ptr<Light> comp)
	{
		float xDis = (Application::activeCam->camTransform->position.x - comp->lightTransform->position.x) * (Application::activeCam->camTransform->position.x - comp->lightTransform->position.x);
		float yDis = (Application::activeCam->camTransform->position.y - comp->lightTransform->position.y) * (Application::activeCam->camTransform->position.y - comp->lightTransform->position.y);
		float zDis = (Application::activeCam->camTransform->position.z - comp->lightTransform->position.z) * (Application::activeCam->camTransform->position.z - comp->lightTransform->position.z);

		comp->distanceToCamera = sqrt(xDis + yDis + zDis);
	}

	void LightSystem::PreRender()
	{
		std::vector<std::shared_ptr<Light>> closestLights;

		Application::standardShader->UseProgram();
		Application::standardShader->BindVector3("u_ViewPos", Application::activeCam->camTransform->position);

		Application::standardShader->BindVector3("u_AmbientLight", Application::activeScene->sceneEnvironment->ambientLightColour);
		Application::standardShader->BindFloat("u_AmbientLightStrength", Application::activeScene->sceneEnvironment->ambientLightStrength);

		Application::standardShader->BindVector3("dirLight.direction", Application::activeScene->sceneEnvironment->directionalLight->direction);
		Application::standardShader->BindVector3("dirLight.diffuseLight", Application::activeScene->sceneEnvironment->directionalLight->diffuseLightColour);
		Application::standardShader->BindVector3("dirLight.specularLight", Application::activeScene->sceneEnvironment->directionalLight->specularLightColour);
		Application::standardShader->BindFloat("dirLight.intensity", Application::activeScene->sceneEnvironment->directionalLight->intensity);

		for (int i = 0; i < Light::componentList.size(); i++)
		{
			if (i < 20)
			{
				closestLights.push_back(Light::componentList.at(i));
				std::sort(closestLights.begin(), closestLights.end(), SortByDistance);
			}
			else
			{
				for (int j = 0; j < closestLights.size(); j++)
				{
					if (Light::componentList.at(i)->distanceToCamera < closestLights.at(j)->distanceToCamera)
					{
						closestLights.pop_back();
						closestLights.push_back(Light::componentList.at(i));
						std::sort(closestLights.begin(), closestLights.end(), SortByDistance);
						break;
					}
				}
			}
		}

		Application::standardShader->BindInt("numberOfLights", closestLights.size());
		for (int i = 0; i < closestLights.size(); i++)
		{
			std::string location = "lights[" + std::to_string(i);

			Application::standardShader->BindVector3(location + "].direction", closestLights.at(i)->lightTransform->rotation);
			Application::standardShader->BindVector3(location + "].position", closestLights.at(i)->lightTransform->position);

			Application::standardShader->BindVector3(location + "].diffuseLight", closestLights.at(i)->diffuseColour);
			Application::standardShader->BindVector3(location + "].specularLight", closestLights.at(i)->specularColour);
			Application::standardShader->BindFloat(location + "].constant", closestLights.at(i)->constant);
			Application::standardShader->BindFloat(location + "].linear", closestLights.at(i)->linear);
			Application::standardShader->BindFloat(location + "].quadratic", closestLights.at(i)->quadratic);
			Application::standardShader->BindFloat(location + "].intensity", closestLights.at(i)->intensity);
		}

		glUseProgram(0);
	}
}