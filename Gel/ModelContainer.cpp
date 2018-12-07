#include "ModelContainer.h"

namespace Gel {

	vector<Model> ModelContainer::modelContainer = vector<Model>();

	void ModelContainer::LoadModel(GLchar* path) {
		modelContainer.push_back(Model(path));
	}
	void ModelContainer::LoadModel(std::string name, GLchar* path) {
		modelContainer.push_back(Model(name, path));
	}

	Model ModelContainer::GetModel(int index) {
		if (index >= 0 && index < modelContainer.size()) {
			return modelContainer[index];
		}
	}

	Model ModelContainer::GetModel(std::string name) {
		for each (Model m in modelContainer)
		{
			if (m.name == name) {
				return m;
			}
		}
	}

}