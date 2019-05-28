#pragma once
#include "Core.h"
#include "Shader.h"
#include "Framebuffer.h"

namespace Gel {

	class GEL_API PostProcessingEffect
	{
	public:
		PostProcessingEffect(GLuint filter = GL_LINEAR);
		~PostProcessingEffect();
		virtual void Use() = 0;
		void BeginCapture();
		void EndCapture();
		void PassScreenTexture(int index);
		void SetActive(bool active);
		bool IsActive();
	protected:
		Shader* shader;
		bool isActive;
	private:
		Framebuffer framebuffer;
	};

}