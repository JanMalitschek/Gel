#pragma once

#include "Material.h"
#include "Texture.h"

class UnlitMaterial : public Gel::Material {
public:
	Gel::Texture texture;
	UnlitMaterial() : Material() {}
	void PassValues() {
		PassTexture("tex", texture.id, GL_TEXTURE0, 0);
	}
};