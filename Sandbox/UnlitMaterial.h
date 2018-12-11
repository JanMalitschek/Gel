#pragma once

#include "Material.h"
#include "Texture.h"

class UnlitMaterial : public Gel::Material {
public:
	Gel::Texture texture;
	glm::vec3 color;
	UnlitMaterial() : Material() {}
	void PassValues() {
		PassTexture("tex", texture.id, GL_TEXTURE0, 0);
		PassColor("col", color);
	}
};