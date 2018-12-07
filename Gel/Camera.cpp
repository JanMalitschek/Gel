#include "Camera.h"

namespace Gel {

	glm::vec3 Camera::position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Camera::front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Camera::right = glm::normalize(glm::cross(up, front));
	glm::mat4 Camera::projection = glm::perspective(RenderSettings::GetFieldOfView(),
													RenderSettings::GetAspectRatio(),
													RenderSettings::GetNearPlane(),
													RenderSettings::GetFarPlane());
	glm::mat4 Camera::view = glm::lookAt(position, position + front, up);

	void Camera::SetPosition(glm::vec3 position) {
		Camera::position = position;
	}

	glm::mat4 Camera::GetProjection() {
		return projection;
	}

	glm::mat4 Camera::GetView() {
		return view;
	}

	glm::mat4 Camera::GetUpdatedView() {
		Camera::view = glm::lookAt(position, position + front, up);
		return view;
	}

	void Camera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
		Camera::projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	}

	void Camera::SetView(glm::vec3 position, glm::vec3 front, glm::vec3 up) {
		Camera::view = glm::lookAt(position, position + front, up);
	}

	void Camera::Translate(glm::vec3 translation) {
		float deltaTime = System::GetDeltaTime();
		position += front * translation.z * deltaTime;
		position += up * -translation.y * deltaTime;
		position += right * -translation.x * deltaTime;
	}

	void Camera::Translate(float x, float y, float z) {
		float deltaTime = System::GetDeltaTime();
		glm::vec3 translation = glm::vec3(x, y, z);
		position += front * translation.z * deltaTime;
		position += up * -translation.y * deltaTime;
		position += right * -translation.x * deltaTime;
	}

	void Camera::SetFront(glm::vec3 front) {
		Camera::front = front;
	}
	void Camera::SetUp(glm::vec3 up) {
		Camera::up = up;
	}
	void Camera::SetRight(glm::vec3 right) {
		Camera::right = right;
	}

	glm::vec3 Camera::GetPosition() {
		return position;
	}

}