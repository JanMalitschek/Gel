#include "Transform.h"

namespace Gel {

	Transform::Transform() {
		this->position = glm::vec3(0.0f, 0.0f, 0.0f);
		this->rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->parent = nullptr;
	}
	Transform::Transform(glm::vec3 position) {
		this->position = position;
		this->rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->parent = nullptr;
	}
	Transform::Transform(glm::vec3 position, glm::vec3 rotation) {
		this->position = position;
		this->rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->forward = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->parent = nullptr;
	}
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->position = position;
		this->rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->scale = scale;
		this->forward = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->right = this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
		this->up = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->parent = nullptr;
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
	void Transform::SetRotation(glm::vec3 rotation) {
		this->rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->forward = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	void Transform::SetRotation(float x, float y, float z) {
		this->rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		this->rotation = glm::rotate(this->rotation, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->rotation = glm::rotate(this->rotation, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->forward = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	void Transform::SetRotation(glm::quat rotation) {
		this->rotation = rotation;
		this->forward = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	void Transform::Rotate(glm::vec3 axis, float angle) {
		glm::quat rot = glm::angleAxis(angle, axis);
		this->rotation = rot * this->rotation;
		this->forward = rot * this->forward;
		this->up = rot * this->up;
		this->right = rot * this->right;
	}
	glm::vec3 Transform::GetEulerAngles() {
		glm::vec3 eulerAngles = glm::eulerAngles(this->rotation);
		eulerAngles.x = glm::degrees(eulerAngles.x);
		eulerAngles.y = glm::degrees(eulerAngles.y);
		eulerAngles.z = glm::degrees(eulerAngles.z);
		return eulerAngles;
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
	void Transform::LookAt(glm::vec3 target, glm::vec3 up)
	{
		this->rotation = glm::toQuat(glm::transpose(glm::lookAt(this->position, target, up)));
		this->forward = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	}
}