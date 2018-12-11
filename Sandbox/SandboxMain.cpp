#include <Gel.h>
#include "UnlitMaterial.h"

void OnCollisionStay(Gel::RigidBodyComponent* other) {
	std::cout << other->sceneObject->name << std::endl;
}

class SandboxApp : public Gel::Application {
public:
	SandboxApp() {

	}
	~SandboxApp() {

	}

	Gel::SceneObject floorObject;
	UnlitMaterial* floorMaterial;
	Gel::SceneObject cubeObject;

	void OnStart() override {
		Gel::EngineHandler::SetWindowTitle("Test Window");
		Gel::RenderSettings::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		Gel::ResourceManager::UnpackResources("Resources/Resources.ger");
		Gel::RenderSettings::SetCullingMode(Gel::CullingMode::CullingMode_Back);
		Gel::RenderSettings::SetDepthTestMode(Gel::DepthTestMode::DepthTest_Enabled);
		Gel::Camera::SetPosition(glm::vec3(0.0f, 3.0f, 15.0f));

		floorMaterial = new UnlitMaterial();
		floorMaterial->texture = Gel::TextureContainer::GetTextureData("Default_Pattern");
		floorMaterial->color = glm::vec3(0.3f, 1.0f, 0.0f);
		floorMaterial->SetShader(Gel::ShaderContainer::GetShader("Unlit"));

		floorObject = Gel::SceneObject("FloorObject", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		floorObject.AddComponent(new Gel::ModelRendererComponent(floorObject.GetTransform()));
		Gel::Model floorModel = Gel::ModelContainer::GetModel("Sample_Floor");
		floorModel.SetMaterial(0, floorMaterial);
		floorObject.GetComponent<Gel::ModelRendererComponent>()->SetModel(floorModel);
		floorObject.AddComponent(new Gel::RigidBodyComponent(floorObject.GetTransform(), Gel::BodyType::Box, 0.0f));
		floorObject.GetComponent<Gel::RigidBodyComponent>()->SetSize(btVector3(8.0f, 0.01f, 8.0f));

		cubeObject = Gel::SceneObject("CubeObject", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		cubeObject.AddComponent(new Gel::ModelRendererComponent(cubeObject.GetTransform()));
		Gel::Model cubeModel = Gel::ModelContainer::GetModel("Sample_Cube");
		cubeModel.SetMaterial(0, floorMaterial);
		cubeObject.GetComponent<Gel::ModelRendererComponent>()->SetModel(cubeModel);
		cubeObject.AddComponent(new Gel::RigidBodyComponent(cubeObject.GetTransform(), Gel::BodyType::Box, 1.0f));
		cubeObject.GetComponent<Gel::RigidBodyComponent>()->SetSize(btVector3(2.0f, 2.0f, 2.0f));
		cubeObject.GetComponent<Gel::RigidBodyComponent>()->OnCollisionExitCallback = OnCollisionStay;
	}
	void OnUpdate() override {
		if (Gel::Input::GetKeyDown(GLFW_KEY_W)) {
			cubeObject.GetComponent<Gel::RigidBodyComponent>()->AddForce(glm::vec3(0.0f, 10.0f, 0.0f), Gel::ForceType::Impulse);
			std::cout << "Jumping" << std::endl;
		}
		if (Gel::Input::GetKeyDown(GLFW_KEY_D)) {
			cubeObject.GetComponent<Gel::RigidBodyComponent>()->AddTorque(glm::vec3(0.0f, 0.0f, -20.0f), Gel::ForceType::Force);
		}
		if (Gel::Input::GetKeyDown(GLFW_KEY_SPACE)) {
			Gel::RaycastHitResult rayHit = Gel::PhysicsEngine::RayCast(Gel::Camera::GetPosition(), glm::vec3(0.0f, 0.0f, -1.0f), 50.0f);
			std::cout << rayHit.hit << std::endl;
		}
		Gel::PhysicsEngine::CheckForCollision();
		floorObject.Update();
		cubeObject.Update();
	}
	void OnTerminate() override {
		
	}
};

Gel::Application* Gel::CreateApplication() {
	return new SandboxApp();
}