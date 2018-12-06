#pragma once
#include "Core.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <iostream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "RenderSettings.h"

namespace Gel {

	enum CursorMode {
		CursorMode_Enabled,
		CursorMode_Hidden,
		CursorMode_Disabled
	};

	static class GEL_API Input {
	public:

		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

		static void SetupCallBacks(GLFWwindow* window);

		//Setter Functions
		static void SetCursorMode(GLFWwindow* window, CursorMode cursorMode);

		//Getter Functions
		static bool GetMouseButton(int button);
		static bool GetMouseButtonDown(int button);
		static bool GetKey(int key);
		static GLfloat GetMouseWheelOffset();
		static GLfloat GetMouseOffset(int axis);
		static GLfloat GetMousePosition(int axis);
		static CursorMode GetCursorMode();

	private:
		static double lastX;
		static double lastY;
		static double mousePosX;
		static double mousePosY;

		static bool firstMouse;

		//Values
		static bool mouseLeft;
		static bool mouseLeftDown;
		static bool mouseMiddle;
		static bool mouseMiddleDown;
		static bool mouseRight;
		static bool mouseRightDown;

		static bool keys[1024];
		static float scrollOffset;
		static float mouseOffsetX;
		static float mouseOffsetY;

		static CursorMode cursorMode;

		static GLFWwindow* window;

		static glm::ivec2 screenDimensions;
	};

}
