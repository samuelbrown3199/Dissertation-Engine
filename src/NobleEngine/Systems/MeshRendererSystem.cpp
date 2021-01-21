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
		RenderMesh(comp);
	}

	void MeshRendererSystem::RenderMesh(std::shared_ptr<MeshRenderer> mesh)
	{
		if (!mesh->transform)
		{
			mesh->transform = GetApplication()->GetEntity(mesh->entityID)->GetComponent<Transform>();
		}
		if (!mesh->shader)
		{
			mesh->shader = Application::standardShader;
			GetApplication()->standardShader->UseProgram();
			GetApplication()->standardShader->BindModelMat(mesh->transform->model);
			GetApplication()->standardShader->BindProjectionMat(GetApplication()->screen->GenerateProjectionMatrix());
			GetApplication()->standardShader->BindViewMat(GetApplication()->activeCam->viewMatrix);
		}
		else
		{
			mesh->shader->UseProgram();
			mesh->shader->BindModelMat(mesh->transform->model);
			mesh->shader->BindProjectionMat(GetApplication()->screen->GenerateProjectionMatrix());
			mesh->shader->BindViewMat(GetApplication()->activeCam->viewMatrix);
		}
		if (mesh->model)
		{
			glBindVertexArray(mesh->model->vaoID);
		}
		if (mesh->material->diffuseTexture)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->material->diffuseTexture->textureID);
		}
		if (mesh->material->specularTexture)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mesh->material->specularTexture->textureID);
		}

		glDrawArrays(GL_TRIANGLES, 0, mesh->model->drawCount);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}