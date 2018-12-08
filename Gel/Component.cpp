#include "Component.h"

namespace Gel {

	Component::Component() {
	
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
