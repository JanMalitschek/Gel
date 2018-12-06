#include "Input.h"

namespace Gel {

	double Input::lastX = 0;
	double Input::lastY = 0;
	glm::ivec2 Input::screenDimensions = RenderSettings::GetScreenDimensions();
	bool Input::firstMouse = true;
	bool Input::keys[1024] = { false };

	bool Input::mouseLeft = false;
	bool Input::mouseMiddle = false;
	bool Input::mouseRight = false;
	bool Input::mouseLeftDown = false;
	bool Input::mouseMiddleDown = false;
	bool Input::mouseRightDown = false;

	float Input::scrollOffset = 0.0f;

	float Input::mouseOffsetX = 0.0f;
	float Input::mouseOffsetY = 0.0f;
	double Input::mousePosX = 0.0f;
	double Input::mousePosY = 0.0f;

	CursorMode Input::cursorMode = CursorMode::CursorMode_Enabled;

	GLFWwindow* Input::window = nullptr;

#pragma region Callbacks

	void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		if (firstMouse) {
			glfwSetCursorPos(window, xpos, ypos);
			mousePosX = xpos;
			mousePosY = ypos;
		}
		else
		{
			mousePosX = xpos;
			mousePosY = ypos;
		}
	}

	void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		scrollOffset = yoffset;
	}

	void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			mouseLeft = true;
		}
		else {
			mouseLeft = false;
		}

		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
			mouseRight = true;
		}
		else {
			mouseRight = false;
		}

		if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
			mouseMiddle = true;
		}
		else {
			mouseMiddle = false;
		}

	}

	void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

#pragma endregion

#pragma region Other Functions

	void Input::SetupCallBacks(GLFWwindow* window) {
		glfwSetCursorPosCallback(window, Input::mouse_callback);
		glfwSetScrollCallback(window, Input::scroll_callback);
		glfwSetKeyCallback(window, Input::key_callback);
		glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
		Input::window = window;
	}

#pragma endregion

#pragma region Getter Functions

	bool Input::GetMouseButton(int button) {
		switch (button) {
		default:
			return false;
		case 0:
			if (mouseLeft)
				return true;
			else
				return false;
		case 1:
			if (mouseRight)
				return true;
			else
				return false;
		case 2:
			if (mouseMiddle)
				return true;
			else
				return false;
		}
	}

	bool Input::GetMouseButtonDown(int button) {
		switch (button) {
		default:
			return false;
		case 0:
			if (mouseLeft && !mouseLeftDown) {
				mouseLeftDown = true;
				return true;
			}
			else if (!mouseLeft && mouseLeftDown) {
				mouseLeftDown = false;
				return false;
			}
			else
			{
				return false;
			}
		case 1:
			if (mouseRight && !mouseRightDown) {
				mouseRightDown = true;
				return true;
			}
			else if (!mouseRight && mouseRightDown) {
				mouseRightDown = false;
				return false;
			}
			else
			{
				return false;
			}
		case 2:
			if (mouseMiddle && !mouseLeftDown) {
				mouseMiddleDown = true;
				return true;
			}
			else if (!mouseMiddle && mouseMiddleDown) {
				mouseMiddleDown = false;
				return false;
			}
			else
			{
				return false;
			}
		}
	}

	bool Input::GetKey(int key) {
		if (keys[key])
			return true;
		else
			return false;
	}

	GLfloat Input::GetMouseWheelOffset() {
		return scrollOffset;
	}

	GLfloat Input::GetMouseOffset(int axis) {
		if (firstMouse) {
			mouse_callback(window, screenDimensions.x / 2, screenDimensions.y / 2);
			lastX = mousePosX;
			lastY = mousePosY;
			firstMouse = false;
			return 0;
		}
		else {
			switch (axis)
			{
			default:
				return 0.0f;
			case 0:
				mouseOffsetX = mousePosX - lastX;
				lastX = mousePosX;
				return mouseOffsetX;
			case 1:
				mouseOffsetY = lastY - mousePosY;
				lastY = mousePosY;
				return mouseOffsetY;
			}
		}
		return 0;
	}

	GLfloat Input::GetMousePosition(int axis) {
		switch (axis)
		{
		default:
			break;
		case 0:
			return mousePosX;
		case 1:
			return mousePosY;
		}
	}

	CursorMode Input::GetCursorMode() {
		return Input::cursorMode;
	}

#pragma endregion

#pragma region Setter Functions

	void Input::SetCursorMode(GLFWwindow* window, CursorMode cursorMode) {
		switch (cursorMode)
		{
		case CursorMode::CursorMode_Enabled:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			Input::cursorMode = cursorMode;
			break;
		case CursorMode::CursorMode_Hidden:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			Input::cursorMode = cursorMode;
			break;
		case CursorMode::CursorMode_Disabled:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Input::cursorMode = cursorMode;
			break;
		default:
			break;
		}
	}

#pragma endregion

}