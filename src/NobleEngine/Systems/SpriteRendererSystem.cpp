#include "SpriteRendererSystem.h"

#include "../EngineCore/Application.h"
#include "../EngineCore/Screen.h"
#include "../Components/Camera.h"

namespace NobleEngine
{
	SetupComponentList(SpriteRenderer);

	void SpriteRendererSystem::OnRender(std::shared_ptr<SpriteRenderer> comp)
	{
		if (!comp->shader)
		{
			comp->shader = Application::standardShader2D;
		}

		comp->shader->UseProgram();
		comp->shader->BindModelMat(comp->transform->model);
		comp->shader->BindProjectionMat(Screen::GenerateOrthographicMatrix());
		comp->shader->BindViewMat(glm::mat4(1.0f));

		glBindVertexArray(comp->rendererVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, comp->sheet->sheet->textureID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}