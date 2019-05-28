#include "Framebuffer.h"
#include "RenderSettings.h"

namespace Gel {

	Framebuffer::Framebuffer()
	{
		textureAttachment = Texture();
		textureAttachment.Create(RenderSettings::GetScreenWidth(), RenderSettings::GetScreenHeight(), GL_LINEAR);
		glGenFramebuffers(1, &FBO);
		std::cout << FBO << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureAttachment.id, 0);
		RBO = Renderbuffer(RenderSettings::GetScreenWidth(), RenderSettings::GetScreenHeight());
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO.RBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: New Framebuffer is not complete!" << std::endl;
		else
		{
			std::cout << "SUCCESS::FRAMEBUFFER:: New Framebuffer is complete" << std::endl;
			std::cout << "ID: " << textureAttachment.id << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::Framebuffer(int width, int height, GLuint filter) {
		textureAttachment = Texture();
		textureAttachment.Create(width, height, filter);
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureAttachment.id, 0);
		RBO = Renderbuffer(width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO.RBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: New Framebuffer is not complete!" << std::endl;
		else
		{
			std::cout << "SUCCESS::FRAMEBUFFER:: New Framebuffer is complete" << std::endl;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer()
	{
	}

	void Framebuffer::Bind() {
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFramebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}

	void Framebuffer::Unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, currentFramebuffer);
	}

}