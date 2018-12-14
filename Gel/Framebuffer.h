#pragma once
#include "Core.h"
#include "Texture.h"
#include "Renderbuffer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Gel {

	class GEL_API Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();
		GLuint FBO;
		Texture textureAttachment;
		Renderbuffer RBO;
	};

}