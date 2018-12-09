#include "SceneObject.h"

namespace Gel {

	SceneObject::SceneObject(vector<Model*> models, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->transform = Transform(position, rotation, scale);
	}

	SceneObject::SceneObject(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->name = name;
		this->transform = Transform(position, rotation, scale);
	}

	void SceneObject::AddComponent(Component* newComponent) {
		components.push_back(newComponent);
	}

	Transform* SceneObject::GetTransform() {
		return &transform;
	}

	void SceneObject::Update() {
		for (auto it : components) {
			it->Update();
		}
	}

	void SceneObject::SetPosition(glm::vec3 position) {
		this->transform.position = position;
	}

	void SceneObject::SetPosition(float x, float y, float z) {
		this->transform.position = glm::vec3(x, y, z);
	}

	void SceneObject::Translate(glm::vec3 translation) {
		this->transform.position += translation * System::GetDeltaTime();
	}

	void SceneObject::Translate(float x, float y, float z) {
		this->transform.position += glm::vec3(x, y, z) * System::GetDeltaTime();
	}

	void SceneObject::AddPosition(glm::vec3 offset) {
		this->transform.position += offset;
	}

	void SceneObject::AddPosition(float x, float y, float z) {
		this->transform.position += glm::vec3(x, y, z);
	}

	void SceneObject::SetRotation(glm::vec3 rotation) {
		this->transform.SetRotation(rotation);
	}

	void SceneObject::SetRotation(float x, float y, float z) {
		this->transform.SetRotation(glm::vec3(x, y, z));
	}

	void SceneObject::Rotate(glm::vec3 axis, float angle) {
		this->transform.Rotate(axis, angle);
	}

	void SceneObject::SetScale(glm::vec3 scale) {
		this->transform.scale = scale;
	}

	void SceneObject::SetScale(float x, float y, float z) {
		this->transform.scale = glm::vec3(x, y, z);
	}

	void SceneObject::Scale(glm::vec3 scale) {
		this->transform.scale += scale * System::GetDeltaTime();
	}

	void SceneObject::Scale(float x, float y, float z) {
		this->transform.scale += glm::vec3(x, y, z) * System::GetDeltaTime();
	}

}