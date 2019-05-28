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

		void SetPosition(glm::vec3 position);
		void SetPosition(float x, float y, float z);
		void Translate(glm::vec3 translation);
		void Translate(float x, float y, float z);

		void SetRotation(glm::vec3 rotation);
		void SetRotation(float x, float y, float z);
		void SetRotation(glm::quat rotation);
		void Rotate(glm::vec3 axis, float angle);
		glm::vec3 GetEulerAngles();

		void SetScale(glm::vec3 scale);
		void SetScale(float x, float y, float z);
		void Scale(glm::vec3 scale);
		void Scale(float x, float y, float z);

		void LookAt(glm::vec3 target, glm::vec3 up);
	};
}