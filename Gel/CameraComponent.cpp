#include "CameraComponent.h"

namespace Gel {

	CameraComponent::CameraComponent(Transform* parentTransform) : Component() {
		this->parentTransform = parentTransform;
		this->isActive = true;
	}
	CameraComponent::CameraComponent() : Component() {
		this->parentTransform = new Transform();
		this->isActive = true;
	}

	void CameraComponent::Update() {
		if (this->isActive) {

			Camera::SetPosition(parentTransform->position);
			Camera::SetFront(-parentTransform->forward);
			Camera::SetUp(parentTransform->up);
			Camera::SetRight(-parentTransform->right);
			Camera::SetView(parentTransform->position, -parentTransform->forward, parentTransform->up);
		}
	}
	void CameraComponent::SetClearColor(glm::vec4 color) {
		this->clearColor = color;
		RenderSettings::SetClearColor(this->clearColor);
	}
	void CameraComponent::SetFOV(GLfloat fov) {
		this->fieldOfView = fov;
		Camera::SetProjection(this->fieldOfView, RenderSettings::GetAspectRatio(), this->nearClippingPlane, this->farClippingPlane);
	}
	void CameraComponent::SetNearClippingPlane(float ncp) {
		this->nearClippingPlane = ncp;
		Camera::SetProjection(this->fieldOfView, RenderSettings::GetAspectRatio(), this->nearClippingPlane, this->farClippingPlane);
	}
	void CameraComponent::SetFarClippingPlane(float fcp) {
		this->farClippingPlane = fcp;
		Camera::SetProjection(this->fieldOfView, RenderSettings::GetAspectRatio(), this->nearClippingPlane, this->farClippingPlane);
	}
	void CameraComponent::SetClippingPlanes(float ncp, float fcp) {
		this->nearClippingPlane = ncp;
		this->farClippingPlane = fcp;
		Camera::SetProjection(this->fieldOfView, RenderSettings::GetAspectRatio(), this->nearClippingPlane, this->farClippingPlane);
	}

}
