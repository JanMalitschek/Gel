#pragma once

#include "Core.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "Transform.h"

namespace Gel {

	class SceneObject;

	class GEL_API Component {
	public:
		Component();
		virtual void Update();
		void SetActive(bool active);
		bool IsActive();
		SceneObject* sceneObject;
	protected:
		Transform* parentTransform;
		bool isActive;
	};
}