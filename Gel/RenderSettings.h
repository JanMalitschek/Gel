#pragma once
#include "Core.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "PostProcessingStack.h"

namespace Gel {

	enum RenderMode {
		RenderMode_Solid,
		RenderMode_Wireframe
	};

	enum CullingMode {
		CullingMode_Front,
		CullingMode_Back,
		CullingMode_None
	};

	enum DepthTestMode {
		DepthTest_Enabled,
		DepthTest_Disabled
	};

	enum BlendMode {
		BlendMode_Default
	};

	struct GEL_API DirectionalLight {
		DirectionalLight(glm::vec3 direction, float intensity, glm::vec3 color) {
			Direction = direction;
			Intensity = intensity;
			Color = color;
		}

		glm::vec3 Direction = glm::vec3(-1, -1, -1);
		float Intensity = 2;
		glm::vec3 Color = glm::vec3(1, 1, 1);
	};

	struct GEL_API AmbientLight {
		AmbientLight(float intensity, glm::vec3 color) {
			Intensity = intensity;
			Color = color;
		}

		float Intensity = 0.3f;
		glm::vec3 Color = glm::vec3(1, 1, 1);
	};

	static class GEL_API RenderSettings {
	public:

		static int GetScreenHeight();
		static int GetScreenWidth();
		static const int GetConstantScreenHeight();
		static const int GetConstantScreenWidth();
		static glm::ivec2 GetScreenDimensions();
		static GLfloat GetAspectRatio();
		static GLfloat GetFieldOfView();
		static RenderMode GetRenderMode();
		static CullingMode GetCullingMode();
		static DepthTestMode GetDepthTestMode();
		static AmbientLight GetAmbientLight();
		static DirectionalLight GetDirectionalLight();
		static float GetNearPlane();
		static float GetFarPlane();
		static int GetGLViewportWidth();
		static int GetGLViewportHeight();
		static bool glewInitialized;
		static PostProcessingStack postProcessingStack;

		static void SetScreenHeight(int height);
		static void SetScreenWidth(int width);
		static void SetScreenDimensions(glm::ivec2 dimensions);
		static void SetScreenDimensions(int widht, int height);
		static void SetFieldOfView(GLfloat fieldofview);
		static void SetRenderMode(RenderMode renderMode);
		static void RestoreRenderMode();
		static void SetCullingMode(CullingMode cullingMode);
		static void RestoreCullingMode();
		static void SetDepthTestMode(DepthTestMode depthTestMode);
		static void RestoreDepthTestMode();
		static void SetBlendMode(BlendMode blendMode);
		static void RestoreBlendMode();
		static void EnableBlending(bool enabled);
		static void SetClearColor(glm::vec4 clearColor);
		static void SetClearColor(float r, float g, float b, float a);
		static void SetClearColor(int r, int g, int b);
		static void SetNearPlane(float nearPlane);
		static void SetFarPlane(float farPlane);
		static void SetAmbientLight(AmbientLight light);
		static void SetDirectionalLight(DirectionalLight light);
		static void SetWindowIcon(GLFWwindow* window);
		static void SetWindowIcon(GLFWwindow* window, const char* path);

		static void RestoreEditViewport();

		static void ClearBuffers();

		static GLFWwindow* SetupWindow();

		static bool runInEditor;
	private:
		static int screenHeight;
		static int screenWidth;
		static GLfloat aspectRatio;
		static GLfloat fov;
		static int glViewportPositionX;
		static int glViewportPositionY;
		static int glViewportWidth;
		static int glViewportHeight;

		static RenderMode renderMode;
		static CullingMode cullingMode;
		static DepthTestMode depthTestMode;
		static BlendMode blendMode;

		static glm::vec4 clearColor;

		static DirectionalLight directionalLight;
		static AmbientLight ambientLight;

		static float nearPlane;
		static float farPlane;

		static void CalculateAspectRatio();

		static bool runningInFullscreen;

	};
}
