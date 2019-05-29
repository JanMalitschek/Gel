#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Shader.h"
#include "DefaultShader.h"
#include "Texture.h"

namespace Gel {

	class GEL_API Material {
	public:
		Material();
		virtual void PassValues();
		void SetShader(Shader* shader);
		void UseShader();
		GLuint GetProgram();
		Shader* shader;

		std::string name;

		//Params
		struct TextureUniform {
			GLuint id;
			std::string uniformName;
			TextureUniform() {
				id = 0;
				uniformName = "";
			}
		};
		std::vector<TextureUniform> textures;
		struct ColorUniform {
			glm::vec4 col;
			std::string uniformName;
			ColorUniform() {
				col = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				uniformName = "";
			}
		};
		std::vector<ColorUniform> colors;
	private:
		DefaultShader defaultShader;
	protected:
		void PassTexture(const char* uniformName, GLuint texture, GLenum activeTexture, int activeTextureID);
		void PassColor(const char* uniformName, glm::vec3 color);
		void PassColorWithAlpha(const char* uniformName, glm::vec4 color);
	};

}

