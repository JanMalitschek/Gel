#include "PostProcessingEffect.h"
#include "RenderSettings.h"

namespace Gel {

	PostProcessingEffect::PostProcessingEffect()
	{
		this->framebuffer = Framebuffer(RenderSettings::GetScreenWidth(), RenderSettings::GetScreenHeight());
	}

	PostProcessingEffect::~PostProcessingEffect()
	{
		delete shader;
	}

	void PostProcessingEffect::PassScreenTexture(int index) {
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, this->framebuffer.textureAttachment.id);
		glUniform1i(glGetUniformLocation(this->shader->GetProgram(), "Gel_ScreenTexture"), index);
	}

	void PostProcessingEffect::BeginCapture() {
		this->framebuffer.Bind();
		RenderSettings::ClearBuffers();
	}
	void PostProcessingEffect::EndCapture() {
		this->framebuffer.Unbind();
		RenderSettings::ClearBuffers();
	}

}