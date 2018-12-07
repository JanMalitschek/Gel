#include "System.h"

namespace Gel {

	GLfloat System::deltaTime = 0.0f;
	GLfloat System::currentFrame = 0.0f;
	GLfloat System::lastFrame = 0.0f;

	void System::ResetDeltaTime() {
		currentFrame = glfwGetTime();
		lastFrame = currentFrame;
	}

	void System::Run() {
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	GLfloat System::GetDeltaTime() {
		return deltaTime;
	}

	GLfloat System::GetTimeElapsed() {
		return currentFrame;
	}

}