#include "MaterialContainer.h"

namespace Gel {
	std::vector<Gel::Material*> MaterialContainer::materials = std::vector<Gel::Material*>();

	void MaterialContainer::AddMaterial(Gel::Material* material) {
		materials.push_back(material);
	}

	Gel::Material* MaterialContainer::GetMaterial(int index) {
		if (index >= 0 && index < materials.size()) {
			return materials[index];
		}
	}

	Gel::Material* MaterialContainer::GetMaterial(std::string name) {
		for (int i = 0; i < materials.size(); i++) {
			if (materials[i]->name == name)
				return materials[i];
		}
	}
}