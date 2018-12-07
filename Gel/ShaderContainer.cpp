#include "ShaderContainer.h"

namespace Gel {

	std::vector<Shader*> ShaderContainer::shaders = std::vector<Shader*>();
	GLuint ShaderContainer::activeShader = 0;

	void ShaderContainer::LoadShader(Shader* shader) {
		shaders.push_back(shader);
	}

	Shader* ShaderContainer::GetShader(int index) {
		if (index >= 0 && index < shaders.size()) {
			return shaders[index];
		}
		return shaders[0];
	}
	Shader* ShaderContainer::GetShader(std::string name) {
		for (auto it : shaders) {
			if (it->name == name) {
				return it;
			}
		}
		std::cout << "There is no Shader with the name \"" << name << "\"!" << std::endl;
		return nullptr;
	}

	void ShaderContainer::SetActiveShader(GLuint activeShader) {
		ShaderContainer::activeShader = activeShader;
	}

	GLuint ShaderContainer::GetActiveShader() {
		return activeShader;
	}

}