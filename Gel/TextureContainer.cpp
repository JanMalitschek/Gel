#include "TextureContainer.h"
#include <fstream>

namespace Gel {

	int TextureContainer::textureIndex = 0;
	std::vector<Texture> TextureContainer::textureContainer = std::vector<Texture>();

	void TextureContainer::LoadTexture(const char* path, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT) {
		textureContainer.push_back(Texture());
		textureContainer[textureContainer.size() - 1].Load(path, wrapModeS, wrapModeT, filterS, filterT);
		textureIndex++;
	}

	void TextureContainer::LoadTexture(const char* path, std::string name, GLint wrapModeS, GLint wrapModeT, GLint filterS, GLint filterT) {
		std::ifstream f(path);
		if (f.good()) {
			textureContainer.push_back(Texture());
			textureContainer[textureContainer.size() - 1].Load(path, wrapModeS, wrapModeT, filterS, filterT);
			textureContainer[textureContainer.size() - 1].name = name;
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