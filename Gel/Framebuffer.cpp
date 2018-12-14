#include "Framebuffer.h"
#include "RenderSettings.h"

namespace Gel {

	Framebuffer::Framebuffer()
	{
		textureAttachment = Texture();
		textureAttachment.Create(RenderSettings::GetScreenWidth(), RenderSettings::GetScreenHeight());
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureAttachment.id, 0);
		RBO = Renderbuffer(RenderSettings::GetScreenWidth(), RenderSettings::GetScreenHeight());
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO.RBO);
	}

	Framebuffer::~Framebuffer()
	{
	}

}