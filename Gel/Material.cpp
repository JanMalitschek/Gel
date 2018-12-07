#include "Material.h"

namespace Gel {

	Material::Material()
	{
		shader = nullptr;
		defaultShader = DefaultShader();
	}

	void Material::PassValues() {

	}

	void Material::SetShader(Shader* shader) {
		this->shader = shader;
	}

	void Material::UseShader() {
		if (this->shader != nullptr) {
			this->shader->Use();
		}
		else {
			this->defaultShader.Use();
		}
	}
}