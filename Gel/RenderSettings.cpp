#include "RenderSettings.h"
#include <soil\SOIL.h>
#include "EngineHandler.h"

namespace Gel {

	int RenderSettings::screenHeight = 600;
	int RenderSettings::screenWidth = 800;
	GLfloat RenderSettings::aspectRatio = 1.334f;
	GLfloat RenderSettings::fov = 45.0f;
	int RenderSettings::glViewportPositionX = 0;
	int RenderSettings::glViewportPositionY = 0;
	int RenderSettings::glViewportWidth = 800;
	int RenderSettings::glViewportHeight = 600;

	float RenderSettings::nearPlane = 0.1f;
	float RenderSettings::farPlane = 100.0f;

	glm::vec4 RenderSettings::clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	RenderMode RenderSettings::renderMode = RenderMode::RenderMode_Solid;
	CullingMode RenderSettings::cullingMode = CullingMode::CullingMode_Back;
	DepthTestMode RenderSettings::depthTestMode = DepthTestMode::DepthTest_Enabled;
	BlendMode RenderSettings::blendMode = BlendMode::BlendMode_Default;
	unsigned int RenderSettings::renderLayerFlags = RenderLayers::Default;

	DirectionalLight RenderSettings::directionalLight = DirectionalLight(glm::vec3(-1.0f, -1.0f, -1.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	AmbientLight RenderSettings::ambientLight = AmbientLight(0.3f, glm::vec3(1.0f, 1.0f, 1.0f));

	bool RenderSettings::runningInFullscreen = false;

	bool RenderSettings::runInEditor = false;

	bool RenderSettings::glewInitialized = false;
	PostProcessingStack RenderSettings::postProcessingStack = PostProcessingStack();

	//Internal
	void RenderSettings::CalculateAspectRatio() {
		aspectRatio = (GLfloat)glViewportWidth / (GLfloat)glViewportHeight;
	}

	//Other
	void RenderSettings::ClearBuffers() {
		glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//Getter
	int RenderSettings::GetScreenHeight() {
		return screenHeight;
	}

	int RenderSettings::GetScreenWidth() {
		return screenWidth;
	}

	const int RenderSettings::GetConstantScreenHeight() {
		return const_cast<int&>(screenHeight);
	}

	const int RenderSettings::GetConstantScreenWidth() {
		return const_cast<int&>(screenWidth);
	}

	glm::ivec2 RenderSettings::GetScreenDimensions() {
		return glm::ivec2(screenWidth, screenHeight);
	}

	GLfloat RenderSettings::GetAspectRatio() {
		return aspectRatio;
	}

	GLfloat RenderSettings::GetFieldOfView() {
		return fov;
	}

	RenderMode RenderSettings::GetRenderMode() {
		return renderMode;
	}

	CullingMode RenderSettings::GetCullingMode() {
		return cullingMode;
	}

	DepthTestMode RenderSettings::GetDepthTestMode() {
		return depthTestMode;
	}

	unsigned int RenderSettings::GetRenderLayerFlags() {
		return renderLayerFlags;
	}

	AmbientLight RenderSettings::GetAmbientLight() {
		return ambientLight;
	}

	DirectionalLight RenderSettings::GetDirectionalLight() {
		return directionalLight;
	}

	float RenderSettings::GetNearPlane() {
		return nearPlane;
	}

	float RenderSettings::GetFarPlane() {
		return farPlane;
	}

	int RenderSettings::GetGLViewportWidth() {
		return glViewportWidth;
	}

	int RenderSettings::GetGLViewportHeight() {
		return glViewportHeight;
	}

	//Setter
	void RenderSettings::SetScreenHeight(int height) {
		screenHeight = height;
		glViewportWidth = screenWidth;
		glViewportHeight = screenHeight;
		CalculateAspectRatio();
		if (!runningInFullscreen) {
			glViewport(glViewportPositionX, glViewportPositionY, glViewportWidth, glViewportHeight);
			glfwSetWindowSize(EngineHandler::window, screenWidth, screenHeight);
		}
		else
		{
			//RenderSettings::glViewportWidth = videoMode->width;
			//RenderSettings::glViewportHeight = videoMode->height;
			//glViewport(glViewportPositionX, glViewportPositionY, videoMode->width, videoMode->height);
		}
	}

	void RenderSettings::SetScreenWidth(int width) {
		screenWidth = width;
		glViewportWidth = screenWidth;
		glViewportHeight = screenHeight;
		CalculateAspectRatio();
		if (!runningInFullscreen) {
			glViewport(glViewportPositionX, glViewportPositionY, glViewportWidth, glViewportHeight);
			glfwSetWindowSize(EngineHandler::window, screenWidth, screenHeight);
		}
		else
		{
			//RenderSettings::glViewportWidth = videoMode->width;
			//RenderSettings::glViewportHeight = videoMode->height;
			//glViewport(glViewportPositionX, glViewportPositionY, videoMode->width, videoMode->height);
		}
	}

	void RenderSettings::SetScreenDimensions(glm::ivec2 dimensions) {
		screenWidth = dimensions.x;
		screenHeight = dimensions.y;
		glViewportWidth = screenWidth;
		glViewportHeight = screenHeight;
		CalculateAspectRatio();
		if (!runningInFullscreen) {
			glViewport(glViewportPositionX, glViewportPositionY, glViewportWidth, glViewportHeight);
			glfwSetWindowSize(EngineHandler::window, screenWidth, screenHeight);
		}
		else
		{
			//RenderSettings::glViewportWidth = videoMode->width;
			//RenderSettings::glViewportHeight = videoMode->height;
			//glViewport(glViewportPositionX, glViewportPositionY, videoMode->width, videoMode->height);
		}
	}

	void RenderSettings::SetScreenDimensions(int width, int height) {
		screenWidth = width;
		screenHeight = height;
		glViewportWidth = screenWidth;
		glViewportHeight = screenHeight;
		CalculateAspectRatio();
		if (!runningInFullscreen) {
			glViewport(glViewportPositionX, glViewportPositionY, glViewportWidth, glViewportHeight);
			glfwSetWindowSize(EngineHandler::window, screenWidth, screenHeight);
		}
		else
		{
			//RenderSettings::glViewportWidth = videoMode->width;
			//RenderSettings::glViewportHeight = videoMode->height;
			//glViewport(glViewportPositionX, glViewportPositionY, videoMode->width, videoMode->height);
		}
	}

	void RenderSettings::SetFieldOfView(GLfloat fieldofview) {
		fov = fieldofview;
	}

	void RenderSettings::SetRenderMode(RenderMode renderMode) {
		RenderSettings::renderMode = renderMode;
		switch (renderMode)
		{
		case RenderMode::RenderMode_Solid:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case RenderMode::RenderMode_Wireframe:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		default:
			break;
		}
	}

	void RenderSettings::RestoreRenderMode() {
		switch (RenderSettings::renderMode)
		{
		case RenderMode::RenderMode_Solid:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case RenderMode::RenderMode_Wireframe:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		default:
			break;
		}
	}

	void RenderSettings::SetCullingMode(CullingMode cullingMode) {
		RenderSettings::cullingMode = cullingMode;
		switch (cullingMode)
		{
		case CullingMode::CullingMode_Front:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;
		case CullingMode::CullingMode_Back:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		case CullingMode::CullingMode_None:
			glDisable(GL_CULL_FACE);
			break;
		default:
			break;
		}
	}

	void RenderSettings::RestoreCullingMode() {
		switch (RenderSettings::cullingMode)
		{
		case CullingMode::CullingMode_Front:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;
		case CullingMode::CullingMode_Back:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		case CullingMode::CullingMode_None:
			glDisable(GL_CULL_FACE);
			break;
		default:
			break;
		}
	}

	void RenderSettings::SetRenderLayerFlags(unsigned int renderLayerFlags) {
		RenderSettings::renderLayerFlags = renderLayerFlags;
	}

	void RenderSettings::SetClearColor(glm::vec4 clearColor) {
		RenderSettings::clearColor = clearColor;
	}

	void RenderSettings::SetClearColor(float r, float g, float b, float a) {
		RenderSettings::clearColor = glm::vec4(r, g, b, a);
	}

	void RenderSettings::SetClearColor(int r, int g, int b) {
		RenderSettings::clearColor = glm::vec4(r * 0.0039f, g * 0.0039f, b * 0.0039f, 0.0f);
	}

	void RenderSettings::SetDepthTestMode(DepthTestMode depthTestMode) {
		RenderSettings::depthTestMode = depthTestMode;
		glDepthFunc(GL_LEQUAL);
		switch (depthTestMode)
		{
		default:
			break;
		case DepthTestMode::DepthTest_Enabled:
			glEnable(GL_DEPTH_TEST);
			break;
		case DepthTestMode::DepthTest_Disabled:
			glDisable(GL_DEPTH_TEST);
			break;
		}
	}

	void RenderSettings::RestoreDepthTestMode() {
		glDepthFunc(GL_LEQUAL);
		switch (RenderSettings::depthTestMode)
		{
		default:
			break;
		case DepthTestMode::DepthTest_Enabled:
			glEnable(GL_DEPTH_TEST);
			break;
		case DepthTestMode::DepthTest_Disabled:
			glDisable(GL_DEPTH_TEST);
			break;
		}
	}

	void RenderSettings::SetBlendMode(BlendMode blendMode) {
		RenderSettings::blendMode = blendMode;
		switch (blendMode)
		{
		default:
			break;
		case BlendMode::BlendMode_Default:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}

	void RenderSettings::RestoreBlendMode() {
		switch (RenderSettings::blendMode)
		{
		default:
			break;
		case BlendMode::BlendMode_Default:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}

	void RenderSettings::EnableBlending(bool enabled) {
		if (enabled)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}

	void RenderSettings::SetNearPlane(float nearPlane) {
		RenderSettings::nearPlane = nearPlane;
	}

	void RenderSettings::SetFarPlane(float farPlane) {
		RenderSettings::farPlane = farPlane;
	}

	void RenderSettings::SetAmbientLight(AmbientLight light) {
		ambientLight = light;
	}

	void RenderSettings::SetDirectionalLight(DirectionalLight light) {
		directionalLight = light;
	}

	void RenderSettings::SetWindowIcon(GLFWwindow* window) {
		GLFWimage icons[1];
		icons[0].pixels = SOIL_load_image("Engine/Textures/Default_Icon.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
		glfwSetWindowIcon(window, 1, icons);
		SOIL_free_image_data(icons[0].pixels);
	}

	void RenderSettings::SetWindowIcon(GLFWwindow* window, const char* path) {
		GLFWimage icons[1];
		icons[0].pixels = SOIL_load_image(path, &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
		glfwSetWindowIcon(window, 1, icons);
		SOIL_free_image_data(icons[0].pixels);
	}

	void RenderSettings::RestoreEditViewport() {
		glViewport(glViewportPositionX, glViewportPositionY, glViewportWidth, glViewportHeight);
	}

	GLFWwindow*  RenderSettings::SetupWindow() {

		GLFWwindow *window;
		//Initialize GLFW
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		if (runInEditor) {
			glfwWindowHint(GLFW_DECORATED, false);
		}
		const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (!runningInFullscreen) {
			window = glfwCreateWindow(screenWidth, screenHeight, "Hello Gel!", nullptr, nullptr);
			glfwSetWindowPos(window, 100, 100);
		}
		else
		{
			window = glfwCreateWindow(videoMode->width, videoMode->height, "Hello Gel!", glfwGetPrimaryMonitor(), nullptr);
			RenderSettings::SetScreenDimensions(videoMode->width, videoMode->height);
		}
		if (window == nullptr) {

			std::cout << "Couldnt create a window!" << std::endl;
			glfwTerminate();

		}
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		
		if (glewInit() != GLEW_OK) {
			std::cout << "Couldnt initialize GLEW!" << std::endl;
		}
		glewInitialized = true;

		//Set the OpenGL viewport
		if (!runningInFullscreen) {
			glViewport(glViewportPositionX, glViewportPositionY, glViewportWidth, glViewportHeight);
		}
		else
		{
			RenderSettings::glViewportWidth = videoMode->width;
			RenderSettings::glViewportHeight = videoMode->height;
			glViewport(glViewportPositionX, glViewportPositionY, videoMode->width, videoMode->height);
		}
		CalculateAspectRatio();
		return window;
	}

}