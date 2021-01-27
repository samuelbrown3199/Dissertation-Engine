#include "LightSystem.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"

namespace NobleEngine
{
	SetupComponentList(Light);

	void LightSystem::PreRender()
	{
		Application::standardShader->UseProgram();

		Application::standardShader->BindVector3("u_ViewPos", Application::activeCam->camTransform->position);
		Application::standardShader->BindVector3("u_AmbientLight", glm::vec3(1.0f, 1.0f, 1.0f));
		Application::standardShader->BindFloat("u_AmbientLightStrength", 0.1f);

		Application::standardShader->BindVector3("lights.direction", glm::vec3(-10, -20, -10));
		Application::standardShader->BindVector3("lights.diffuseLight", glm::vec3(1.0, 1.0, 1.0));
		Application::standardShader->BindVector3("lights.specularLight", glm::vec3(1.0, 1.0, 1.0));

		glUseProgram(0);
	}

	void LightSystem::OnRender(std::shared_ptr<Light> comp)
	{

	}
}