#include "Material.h"

namespace Gel {

	Material::Material()
	{
		shader = nullptr;
		defaultShader = DefaultShader();
		textures = std::vector<TextureUniform>();
		colors = std::vector<ColorUniform>();
	}

	void Material::PassValues() {
		for (int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			glUniform1i(glGetUniformLocation(GetProgram(), textures[i].uniformName.c_str()), i);
		}
		for (int i = 0; i < colors.size(); i++) {
			glUniform4f(glGetUniformLocation(GetProgram(), colors[i].uniformName.c_str()), colors[i].col.r, colors[i].col.g, colors[i].col.b, colors[i].col.a);
		}
	}

	void Material::SetShader(Shader* shader) {
		this->shader = shader;
	}

	GLuint Material::GetProgram() {
		if (this->shader != nullptr) {
			return this->shader->Program;
		}
		else {
			this->defaultShader.GetProgram();
		}
	}

	void Material::UseShader() {
		if (this->shader != nullptr) {
			this->shader->Use();
		}
		else {
			this->defaultShader.Use();
		}
	}

	void Material::PassTexture(const char* uniformName, GLuint texture, GLenum activeTexture, int activeTextureID) {
		glActiveTexture(activeTexture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(GetProgram(), uniformName), activeTextureID);
	}
	void Material::PassColor(const char* uniformName, glm::vec3 color) {
		glUniform3f(glGetUniformLocation(GetProgram(), uniformName), color.r, color.g, color.b);
	}
	void Material::PassColorWithAlpha(const char* uniformName, glm::vec4 color) {
		glUniform4f(glGetUniformLocation(GetProgram(), uniformName), color.r, color.g, color.b, color.a);
	}
}