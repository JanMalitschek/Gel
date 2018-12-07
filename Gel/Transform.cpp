#include "Transform.h"

namespace Gel {

	Transform::Transform() {
		this->position = glm::vec3(0.0f, 0.0f, 0.0f);
		this->localRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		this->globalRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	Transform::Transform(glm::vec3 position) {
		this->position = position;
		this->localRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		this->globalRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	Transform::Transform(glm::vec3 position, glm::vec3 rotation) {
		this->position = position;
		glm::quat qx = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qy = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qz = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->globalRotation = qx * qy * qz;
		this->localRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->position = position;
		glm::quat qx = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qy = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qz = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->globalRotation = qx * qy * qz;
		this->localRotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		this->scale = scale;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	void Transform::SetPosition(glm::vec3 position) {
		this->position = position;
	}
	void Transform::SetPosition(float x, float y, float z) {
		this->position = glm::vec3(x, y, z);
	}
	void Transform::Translate(glm::vec3 translation) {
		this->position += translation;
	}
	void Transform::Translate(float x, float y, float z) {
		this->position += glm::vec3(x, y, z);
	}
	void Transform::SetRotation(glm::vec3 rotation, bool local) {
		glm::quat qx = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qy = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qz = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		if (local)
			this->localRotation = qx * qy * qz;
		else
			this->globalRotation = qx * qy * qz;
		this->forward = this->globalRotation * this->localRotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = this->globalRotation * this->localRotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = this->globalRotation * this->localRotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	void Transform::SetRotation(float x, float y, float z, bool local) {
		glm::quat qx = glm::angleAxis(glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::quat qy = glm::angleAxis(glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat qz = glm::angleAxis(glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		if (local)
			this->localRotation = qx * qy * qz;
		else
			this->globalRotation = qx * qy * qz;
		this->forward = this->globalRotation * this->localRotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = this->globalRotation * this->localRotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = this->globalRotation * this->localRotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	void Transform::Rotate(glm::vec3 axis, float angle, bool local) {
		if (local)
			this->localRotation = glm::angleAxis(glm::radians(angle), axis) * this->localRotation;
		else
			this->globalRotation = glm::angleAxis(glm::radians(angle), axis) * this->globalRotation;
		this->forward = this->globalRotation * this->localRotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = this->globalRotation * this->localRotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = this->globalRotation * this->localRotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	void Transform::SetScale(glm::vec3 scale) {
		this->scale = scale;
	}
	void Transform::SetScale(float x, float y, float z) {
		this->scale = glm::vec3(x, y, z);
	}
	void Transform::Scale(glm::vec3 scale) {
		this->scale += scale;
	}
	void Transform::Scale(float x, float y, float z) {
		this->scale += glm::vec3(x, y, z);
	}
}