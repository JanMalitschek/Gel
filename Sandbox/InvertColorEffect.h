#pragma once
#include "PostProcessingEffect.h"
#include "ResourceManager.h"

class InvertColorEffect : public Gel::PostProcessingEffect {
public:
	InvertColorEffect() {
		this->shader = Gel::ShaderContainer::GetShader("InvertColor");
	}
	void Use() override {
		this->shader->Use();
	}
};