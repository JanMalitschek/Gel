#pragma once
#include "PostProcessingEffect.h"
#include "ResourceManager.h"

class PixelationEffect : public Gel::PostProcessingEffect {
public:
	PixelationEffect() : Gel::PostProcessingEffect(GL_NEAREST) {
		this->shader = Gel::ShaderContainer::GetShader("Pixelate");
	}
	void Use() override {
		this->shader->Use();
	}
};
