#include "MeshRendererSystem.h"

#include "../EngineCore/Application.h"
#include "../EngineCore/Screen.h"
#include "../EngineCore/Entity.h"
#include "../Components/Transform.h"
#include "../ResourceManagement/ShaderProgram.h"
#include "../Components/Camera.h"

namespace NobleEngine
{
	SetupComponentList(MeshRenderer);

	void MeshRendererSystem::OnRender(std::shared_ptr<MeshRenderer> comp)
	{
		if (!comp->transform)
		{
			comp->transform = GetApplication()->GetEntity(comp->entityID)->GetComponent<Transform>();
		}
		if (!comp->shader)
		{
			comp->shader = Application::standardShader;
		}

		comp->shader->UseProgram();
		comp->shader->BindModelMat(comp->transform->model);
		comp->shader->BindProjectionMat(GetApplication()->screen->GenerateProjectionMatrix());
		comp->shader->BindViewMat(GetApplication()->activeCam->viewMatrix);
		comp->shader->BindFloat("material.shininess", comp->material->shininess);
		if (comp->model)
		{
			glBindVertexArray(comp->model->vaoID);
		}
		if (comp->material->diffuseTexture)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, comp->material->diffuseTexture->textureID);
		}
		if (comp->material->specularTexture)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, comp->material->specularTexture->textureID);
		}

		glDrawArrays(GL_TRIANGLES, 0, comp->model->drawCount);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}