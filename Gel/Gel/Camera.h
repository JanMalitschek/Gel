#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include "RenderSettings.h"
#include "System.h"

namespace Gel {
	static class GEL_API Camera {
	public:
		static void SetPosition(glm::vec3 position);
		static void Translate(glm::vec3 translation);
		static void Translate(float x, float y, float z);
		static glm::mat4 GetProjection();
		static glm::mat4 GetView();
		static glm::mat4 GetUpdatedView();
		static glm::vec3 GetPosition();
		static void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
		static void SetView(glm::vec3 position, glm::vec3 front, glm::vec3 up);
		static void SetFront(glm::vec3 front);
		static void SetUp(glm::vec3 up);
		static void SetRight(glm::vec3 right);

	private:
		static glm::mat4 projection;
		static glm::mat4 view;
		static glm::vec3 position;
		static glm::vec3 up;
		static glm::vec3 front;
		static glm::vec3 right;
	};
}