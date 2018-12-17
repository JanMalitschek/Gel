#pragma once
#include "PostProcessingEffect.h"
#include "ResourceManager.h"

class PixexlationEffect : public Gel::PostProcessingEffect {
public:
	PixexlationEffect() {
		this->shader = Gel::ShaderContainer::GetShader("Pixelate");
	}
	void Use() override {
		this->shader->Use();
	}
};
