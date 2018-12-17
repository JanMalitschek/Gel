#include "Texture.h"

namespace Gel {

	Texture::Texture(GLuint ID, std::string Name, unsigned int width, unsigned int height) {
		id = ID;
		name = Name;
		this->width = width;
		this->height = height;
	}
	Texture::Texture() {
		id = 0;
		name = "";
		this->width = 0;
		this->height = 0;
	}
	void Texture::Load(const char* path, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT) {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		int width, height;
		unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_AUTO);
		//textureContainer[textureIndex].SetSize(width, height);
		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture::Create(int width, int height) {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	int Texture::GetWidth() {
		return this->width;
	}
	int Texture::GetHeight() {
		return this->height;
	}
}