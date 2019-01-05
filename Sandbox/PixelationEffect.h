#pragma once
#include "PostProcessingEffect.h"
#include "ResourceManager.h"

class PixelationEffect : public Gel::PostProcessingEffect {
public:
	PixelationEffect() {
		this->shader = Gel::ShaderContainer::GetShader("Pixelate");
	}
	void Use() override {
		this->shader->Use();
	}
};
