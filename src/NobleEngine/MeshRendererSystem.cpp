#include "MeshRendererSystem.h"

#include "Application.h"
#include "Entity.h"
#include "Transform.h"

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
		//bind shader
		//bind model matrix from transform to shader

		glBindVertexArray(mesh->model->vaoID);
		glDrawArrays(GL_TRIANGLES, 0, mesh->model->drawCount);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}