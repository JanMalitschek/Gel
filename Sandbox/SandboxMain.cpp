#include <Gel.h>

class SandboxApp : public Gel::Application {
public:
	SandboxApp() {

	}
	~SandboxApp() {

	}
	void OnStart() override {
		Gel::EngineHandler::SetWindowTitle("Test Window");
	}
	void OnUpdate() override {
		if (Gel::Input::GetKey(GLFW_KEY_SPACE)) {
			Gel::EngineHandler::TerminateEngine();
		}
	}
	void OnTerminate() override {
		
	}
};

Gel::Application* Gel::CreateApplication() {
	return new SandboxApp();
}