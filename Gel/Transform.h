#pragma once

#include "Core.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

#include <stdio.h>
#include "System.h"

namespace Gel {
	struct GEL_API Transform {
	public:

		Transform* parent;

		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;

		Transform();
		Transform(glm::vec3 position);
		Transform(glm::vec3 position, glm::vec3 rotation);
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		void Transform::SetPosition(glm::vec3 position);
		void Transform::SetPosition(float x, float y, float z);
		void Transform::Translate(glm::vec3 translation);
		void Transform::Translate(float x, float y, float z);

		void Transform::SetRotation(glm::vec3 rotation);
		void Transform::SetRotation(float x, float y, float z);
		void Transform::SetRotation(glm::quat rotation);
		void Transform::Rotate(glm::vec3 axis, float angle);
		glm::vec3 GetEulerAngles();

		void Transform::SetScale(glm::vec3 scale);
		void Transform::SetScale(float x, float y, float z);
		void Transform::Scale(glm::vec3 scale);
		void Transform::Scale(float x, float y, float z);
	};
}