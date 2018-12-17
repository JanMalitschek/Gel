#pragma once
#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <vector>

#include "Framebuffer.h"

#include "PostProcessingEffect.h"

namespace Gel {

	class GEL_API PostProcessingStack
	{
	public:
		PostProcessingStack();
		~PostProcessingStack();
		void BeginCapture();
		void EndCapture();
		void Process();
		void AddEffect(PostProcessingEffect* newEffect);
		template<class EffectType>
		EffectType* GetComponent() {
			for each(PostProcessingEffect* p in effects) {
				EffectType* tempEffect = dynamic_cast<EffectType*>(c);
				if (tempEffect != nullptr) {
					return tempEffect;
				}
			}
			std::cout << "The PostProcessingStack does not contain an effect of this type!" << std::endl;
			return new EffectType;
		}
	private:
		GLfloat vertices[24] = {
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  1.0f,  1.0f, 1.0f
		};
		GLuint VAO, VBO;
		std::vector<PostProcessingEffect*> effects;
		GLint currentFramebuffer;
	};

}