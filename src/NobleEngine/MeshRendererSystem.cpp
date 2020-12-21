#include "MeshRendererSystem.h"

#include "Application.h"
#include "Screen.h"
#include "Entity.h"
#include "Transform.h"
#include "ShaderProgram.h"
#include "Camera.h"

namespace NobleEngine
{
	SetupComponentList(MeshRenderer);

	void MeshRendererSystem::Render()
	{
		for (size_t mr = 0; mr < MeshRenderer::componentList.size(); mr++)
		{
			RenderMesh(MeshRenderer::componentList.at(mr));
		}
	}

	void MeshRendererSystem::RenderMesh(std::shared_ptr<MeshRenderer> mesh)
	{
		std::shared_ptr<Transform> tr = GetApplication()->GetEntity(mesh->entityID)->GetComponent<Transform>();
		if (!mesh->shader)
		{
			GetApplication()->standardShader->UseProgram();
			GetApplication()->standardShader->BindMat4("u_Model", tr->model);
			GetApplication()->standardShader->BindMat4("u_Projection", GetApplication()->screen->GenerateProjectionMatrix());
			GetApplication()->standardShader->BindMat4("u_View", GetApplication()->activeCam->viewMatrix);

			GetApplication()->standardShader->BindInt("material.diffuseTexture", 0);
			GetApplication()->standardShader->BindInt("material.specularTexture", 1);
		}
		else
		{
			mesh->shader->UseProgram();
			mesh->shader->BindMat4("u_Model", tr->model);
			mesh->shader->BindMat4("u_Projection", GetApplication()->screen->GenerateProjectionMatrix());
			mesh->shader->BindMat4("u_View", GetApplication()->activeCam->viewMatrix);
		}

		glBindVertexArray(mesh->model->vaoID);

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