#include "TextureContainer.h"
#include <fstream>

namespace Gel {

	int TextureContainer::textureIndex = 0;
	std::vector<Texture> TextureContainer::textureContainer = std::vector<Texture>();

	void TextureContainer::LoadTexture(const char* path, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT) {
		textureContainer.push_back(Texture(0, "", 0, 0));
		glGenTextures(1, &textureContainer[textureIndex].id);
		glBindTexture(GL_TEXTURE_2D, textureContainer[textureIndex].id);
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
		glBindTexture(GL_TEXTURE_2D, textureIndex);
		textureIndex++;
	}

	void TextureContainer::LoadTexture(const char* path, std::string name, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT) {
		std::ifstream f(path);
		if (f.good()) {
			textureContainer.push_back(Texture(0, name, 0, 0));
			glGenTextures(1, &textureContainer[textureIndex].id);
			glBindTexture(GL_TEXTURE_2D, textureContainer[textureIndex].id);
			int width, height;
			unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
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
			glBindTexture(GL_TEXTURE_2D, textureIndex);
			textureIndex++;
		}
		else {
			std::cout << "ERROR::TEXTURE_CONTAINER::Could Not Find File " << path << std::endl;
		}
	}

	void TextureContainer::BindTexture(GLuint id, GLenum activeTexture) {
		glActiveTexture(activeTexture);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	GLuint TextureContainer::GetTexture(std::string name) {
		for each (Texture t in textureContainer)
		{
			if (t.name == name) {
				return t.id;
			}
		}
		return 0;
	}

	Texture TextureContainer::GetTextureData(std::string name) {
		for each (Texture t in textureContainer)
		{
			if (t.name == name) {
				return t;
			}
		}
		return Texture(0, "", 0, 0);
	}

	int TextureContainer::GetTextureCount() {
		return textureContainer.size();
	}

	std::string TextureContainer::GetTextureName(int index) {
		return textureContainer[index].name;
	}

	Texture TextureContainer::GetTextureByIndex(int index) {
		return textureContainer[index];
	}

}