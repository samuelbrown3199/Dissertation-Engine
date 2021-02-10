#include "Model.h"

namespace NobleEngine
{
	GLuint PrimitiveShapes::quadVAO;

	void PrimitiveShapes::SetupQuad()
	{
		const GLfloat positions[] =
		{
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		};

		const GLfloat uvs[] =
		{
			0.0, 0.0,
			0.0, 1.0,
			1.0, 1.0,
			1.0, 1.0,
			1.0, 0.0,
			0.0, 0.0
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

		glGenVertexArrays(1, &quadVAO);
		if (!quadVAO)
		{
			throw std::exception();
		}
		glBindVertexArray(quadVAO);

		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	void PrimitiveShapes::SetupPrimitiveShapes()
	{
		SetupQuad();
	}


	void Model::OnLoad()
	{
		vaoID = buLoadModel(resourcePath, &drawCount);
	}
}