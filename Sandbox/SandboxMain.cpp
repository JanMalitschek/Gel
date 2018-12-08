#include <Gel.h>
#include "UnlitMaterial.h"

class SandboxApp : public Gel::Application {
public:
	SandboxApp() {

	}
	~SandboxApp() {

	}
	Gel::SceneObject floorObject;
	Gel::ModelRendererComponent* modelRenderer;
	UnlitMaterial* floorMaterial;
	void OnStart() override {
		Gel::EngineHandler::SetWindowTitle("Test Window");
		Gel::RenderSettings::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		Gel::ResourceManager::UnpackResources("Resources/Resources.ger");
		Gel::RenderSettings::SetCullingMode(Gel::CullingMode::CullingMode_Back);
		Gel::Camera::SetPosition(glm::vec3(0.0f, 3.0f, 15.0f));

		floorMaterial = new UnlitMaterial();
		floorMaterial->texture = Gel::TextureContainer::GetTextureData("Default_Pattern");
		floorMaterial->SetShader(Gel::ShaderContainer::GetShader("Unlit"));
		floorObject = Gel::SceneObject("FloorObject", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		modelRenderer = new Gel::ModelRendererComponent(floorObject.GetTransform());
		Gel::Model floorModel = Gel::ModelContainer::GetModel("Sample_Floor");
		floorModel.SetMaterial(0, floorMaterial);
		modelRenderer->SetModel(floorModel);
		floorObject.AddComponent(modelRenderer);
	}
	void OnUpdate() override {
		if (Gel::Input::GetKey(GLFW_KEY_SPACE)) {
			Gel::EngineHandler::TerminateEngine();
		}
		floorObject.Update();
	}
	void OnTerminate() override {
		
	}
};

Gel::Application* Gel::CreateApplication() {
	return new SandboxApp();
}