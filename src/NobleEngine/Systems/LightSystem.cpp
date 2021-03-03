#include "LightSystem.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"
#include "../EngineCore/ResourceManager.h"
#include "../EngineCore/Scene.h"

namespace NobleEngine
{
	SetupComponentList(Light);

	void LightSystem::PreRender()
	{
		Application::standardShader->UseProgram();

		Application::standardShader->BindInt("numberOfLights", Light::componentList.size());
		Application::standardShader->BindVector3("u_ViewPos", Application::activeCam->camTransform->position);

		Application::standardShader->BindVector3("u_AmbientLight", Application::activeScene->sceneEnvironment->ambientLightColour);
		Application::standardShader->BindFloat("u_AmbientLightStrength", Application::activeScene->sceneEnvironment->ambientLightStrength);

		Application::standardShader->BindVector3("dirLight.direction", Application::activeScene->sceneEnvironment->directionalLight->direction);
		Application::standardShader->BindVector3("dirLight.diffuseLight", Application::activeScene->sceneEnvironment->directionalLight->diffuseLightColour);
		Application::standardShader->BindVector3("dirLight.specularLight", Application::activeScene->sceneEnvironment->directionalLight->specularLightColour);
		Application::standardShader->BindFloat("dirLight.intensity", Application::activeScene->sceneEnvironment->directionalLight->intensity);

		for (int i = 0; i < Light::componentList.size(); i++)
		{
			std::string location = "lights[" + std::to_string(i);

			Application::standardShader->BindVector3(location + "].direction", Light::componentList.at(i)->lightTransform->rotation);
			Application::standardShader->BindVector3(location + "].position", Light::componentList.at(i)->lightTransform->position);

			Application::standardShader->BindVector3(location + "].diffuseLight", Light::componentList.at(i)->diffuseColour);
			Application::standardShader->BindVector3(location + "].specularLight", Light::componentList.at(i)->specularColour);
			Application::standardShader->BindFloat(location + "].constant", Light::componentList.at(i)->constant);
			Application::standardShader->BindFloat(location + "].linear", Light::componentList.at(i)->linear);
			Application::standardShader->BindFloat(location + "].quadratic", Light::componentList.at(i)->quadratic);
			Application::standardShader->BindFloat(location + "].intensity", Light::componentList.at(i)->intensity);
		}

		glUseProgram(0);
	}

	void LightSystem::OnRender(std::shared_ptr<Light> comp)
	{

	}
}