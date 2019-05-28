#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <vector>
#include <soil/SOIL.h>
#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Texture.h"

namespace Gel {

	static class GEL_API TextureContainer {
	public:
		static void LoadTexture(const char* path, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT);
		static void LoadTexture(const char* path, std::string name, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT);
		static void BindTexture(GLuint id, GLenum activeTexture);
		static GLuint GetTexture(std::string name);
		static Texture GetTextureData(std::string name);
		static Texture GetTextureByIndex(int index);
		static int GetTextureCount();
		static std::string GetTextureName(int index);
	private:
		static int textureIndex;
		static std::vector<Texture> textureContainer;

	};

}