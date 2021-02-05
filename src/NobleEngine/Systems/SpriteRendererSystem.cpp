#include "SpriteRendererSystem.h"

#include "../EngineCore/Application.h"
#include "../EngineCore/Screen.h"
#include "../Components/Camera.h"

namespace NobleEngine
{
	SetupComponentList(SpriteRenderer);

	void SpriteRendererSystem::OnRender(std::shared_ptr<SpriteRenderer> comp)
	{
		/*if (comp->sprite != comp->oldSprite)
		{
			const GLfloat positions[] =
			{
				-0.5f, 0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f
			};

			/*const GLfloat uvs[] =
			{
				comp->sprite->xPos, comp->sprite->yPos,
				comp->sprite->xPos, comp->sprite->height,
				comp->sprite->width, comp->sprite->yPos,
				comp->sprite->xPos, comp->sprite->height,
				comp->sprite->width, comp->sprite->height,
				comp->sprite->width, comp->sprite->yPos
			};
			const GLfloat uvs[] =
			{
				0.0, 0.0,
				0.0, 1.0,
				1.0, 0.0,
				0.0, 1.0,
				1.0, 1.0,
				1.0, 0.0
			};

			GLuint positionsVBO = 0;
			glGenBuffers(1, &positionsVBO);
			if (!positionsVBO)
			{
				throw std::exception();
			}
			glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint uvVBO = 0;
			glGenBuffers(1, &uvVBO);
			if (!uvVBO)
			{
				throw std::exception();
			}
			glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			if (!comp->rendererVAO)
			{
				glGenVertexArrays(1, &comp->rendererVAO);
			}
			if (!comp->rendererVAO)
			{
				throw std::exception();
			}
			glBindVertexArray(comp->rendererVAO);

			glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);

			comp->oldSprite = comp->sprite;
		}*/

		if (!comp->shader)
		{
			comp->shader = Application::standardShader2D;
		}

		comp->shader->UseProgram();
		comp->shader->BindModelMat(glm::mat4(1.0f));
		comp->shader->BindProjectionMat(glm::mat4(1.0f));
		comp->shader->BindViewMat(glm::mat4(1.0f));

		glBindVertexArray(comp->rendererVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, comp->sheet->sheet->textureID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}