#pragma once

#include "Core.h"

#include "Component.h"
#include "Model.h"
#include "Material.h"
#include "Transform.h"

namespace Gel {
	class GEL_API ModelRendererComponent : public Component {
	public:
		ModelRendererComponent(Transform* parentTransform);
		ModelRendererComponent();
		void Update();
		void SetModel(Model model);
		void SetMaterials(vector<Material*> materials);
		int GetMaterialCount();
		Material* GetMaterial(int index);
		Model model;
	private:
		std::vector<Material*> materials;
	};
}