#include "PostProcessingStack.h"
#include "RenderSettings.h"

namespace Gel {

	PostProcessingStack::PostProcessingStack()
	{
		if (RenderSettings::glewInitialized) {
			glGenVertexArrays(1, &this->VAO);
			glGenBuffers(1, &this->VBO);

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
			glBindVertexArray(0);

		}
	}


	PostProcessingStack::~PostProcessingStack()
	{
	}

	void PostProcessingStack::BeginCapture()
	{
		if (this->effects.size() > 0) {
			this->effects[0]->BeginCapture();
		}
	}

	void PostProcessingStack::EndCapture()
	{
		if (this->effects.size() > 0) {
			this->effects[0]->EndCapture();
		}
	}

	void PostProcessingStack::Process()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFramebuffer);
		for (int i = 0; i < this->effects.size(); i++) {
			if (i + 1 < this->effects.size()) {
				this->effects[i + 1]->BeginCapture();
				this->effects[i]->Use();
				this->effects[i]->PassScreenTexture(i);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
				this->effects[i + 1]->EndCapture();
			}
			else {
				glBindFramebuffer(GL_FRAMEBUFFER, currentFramebuffer);
				this->effects[i]->Use();
				this->effects[i]->PassScreenTexture(i);
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
			}
		}
	}

	void PostProcessingStack::AddEffect(PostProcessingEffect* newEffect) {
		this->effects.push_back(newEffect);
	}

}