#include "ModelRendererComponent.h"

namespace Gel {
	ModelRendererComponent::ModelRendererComponent(Transform* parentTransform) : Component() {
		this->parentTransform = parentTransform;
		this->isActive = true;
	}
	ModelRendererComponent::ModelRendererComponent() : Component() {
		this->parentTransform = new Transform();
		this->isActive = true;
	}
	void ModelRendererComponent::Update() {
		if (this->isActive) {
			model.Draw(*this->parentTransform);
		}
	}
	void ModelRendererComponent::SetModel(Model model) {
		this->model = model;
	}
	void ModelRendererComponent::SetMaterials(vector<Material*> materials) {
		this->materials = materials;
		this->model.SetMaterials(this->materials);
	}
	int ModelRendererComponent::GetMaterialCount() {
		return this->materials.size();
	}
	Material* ModelRendererComponent::GetMaterial(int index) {
		return materials[index];
	}
}