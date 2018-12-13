#pragma once

#include "Component.h"
#include "SceneObject.h"
#include "Core.h"

namespace Gel {
	class GEL_API CameraComponent : public Gel::Component {
	public:
		CameraComponent(Transform* parentTransform);
		CameraComponent();
		void Update();
		void SetClearColor(glm::vec4 color);
		void SetFOV(GLfloat fov);
		void SetNearClippingPlane(float ncp);
		void SetFarClippingPlane(float fcp);
		void SetClippingPlanes(float ncp, float fcp);

	private:
		glm::vec4 clearColor;
		GLfloat fieldOfView;
		float nearClippingPlane, farClippingPlane;
	};
}