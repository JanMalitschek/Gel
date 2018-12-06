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
	int Texture::GetWidth() {
		return this->width;
	}
	int Texture::GetHeight() {
		return this->height;
	}
}