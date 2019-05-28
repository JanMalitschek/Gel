#include "SceneObject.h"
#include "EngineHandler.h"

namespace Gel {

	SceneObject::SceneObject() {
		this->transform = Transform();
		EngineHandler::sceneObjects.push_back(this);
		renderLayer = RenderLayers::Default;
		this->components = vector<Gel::Component*>();
	}

	SceneObject::SceneObject(vector<Model*> models, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->transform = Transform(position, rotation, scale);
		EngineHandler::sceneObjects.push_back(this);
		renderLayer = RenderLayers::Default;
		this->components = vector<Gel::Component*>();
	}

	SceneObject::SceneObject(std::string name, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->name = name;
		this->transform = Transform(position, rotation, scale);
		EngineHandler::sceneObjects.push_back(this);
		renderLayer = RenderLayers::Default;
		this->components = vector<Gel::Component*>();
	}

	void SceneObject::AddComponent(Component* newComponent) {
		components.push_back(newComponent);
		components[components.size() - 1]->sceneObject = this;
	}

	Transform* SceneObject::GetTransform() {
		return &transform;
	}

	void SceneObject::Update() {
		for (int i = 0; i < this->components.size(); i++) {
			this->components[i]->Update();
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

	SceneObject* SceneObject::Instantiate(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		EngineHandler::instancedSceneObjects.push_back(new SceneObject(*this));
		int index = EngineHandler::instancedSceneObjects.size() - 1;
		for (int i = 0; i < EngineHandler::instancedSceneObjects[index]->GetNumComponents(); i++) {
			EngineHandler::instancedSceneObjects[index]->GetUncastedComponent(i)->SetParentTransform(EngineHandler::instancedSceneObjects[index]->GetTransform());
		}
		EngineHandler::instancedSceneObjects[index]->ResetTransform();
		EngineHandler::instancedSceneObjects[index]->SetPosition(position);
		EngineHandler::instancedSceneObjects[index]->SetRotation(rotation);
		EngineHandler::instancedSceneObjects[index]->SetScale(scale);
		return EngineHandler::instancedSceneObjects[index];
	}

	void SceneObject::ResetTransform() {
		this->transform = Transform();
	}

	int SceneObject::GetNumComponents() {
		return this->components.size();
	}
	Component* SceneObject::GetUncastedComponent(int index) {
		if (index >= 0 && index < this->components.size()) {
			return this->components[index];
		}
		else {
			return nullptr;
		}
	}

}