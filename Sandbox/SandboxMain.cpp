#include <Gel.h>

class SandboxApp : public Gel::Application {
public:
	SandboxApp() {

	}
	~SandboxApp() {

	}
};

Gel::Application* Gel::CreateApplication() {
	return new SandboxApp();
}