#include "Component.h"
#include "SceneObject.h"

namespace Gel {

	Component::Component() {
		this->sceneObject = nullptr;
	};
	void Component::Update() {
	
	};
	void Component::SetActive(bool active) {
		isActive = active;
	};
	bool Component::IsActive() {
		return isActive;
	};

}
