#pragma once

#include "Core.h"
#include "PhysicsEngine.h"
#include "Component.h"
#include "Mesh.h"

#include <functional>

namespace Gel {

	class GEL_API RigidBodyComponent : public Component
	{
	public:
		typedef void(*CollisionCallback)(RigidBodyComponent* other);
		RigidBodyComponent(Transform* parentTransform, BodyType type, float mass, Gel::Mesh mesh = Gel::Mesh());
		RigidBodyComponent();
		void Update();
		void SetSize(btVector3 size);
		void SetRadius(btScalar radius);
		void SetRadiusAndHeight(btScalar radius, btScalar height);
		void SetBounciness(btScalar bounciness);
		void SetFriction(btScalar friction);
		void SetRollingFriction(btScalar rollingFriction);
		void AddForce(glm::vec3 force, ForceType forceType);
		void AddTorque(glm::vec3 torque, ForceType torqueType);
		void Colliding(RigidBodyComponent* other);
		std::function<void(RigidBodyComponent* other)> OnCollisionEnterCallback;
		std::function<void(RigidBodyComponent* other)> OnCollisionStayCallback;
		std::function<void(RigidBodyComponent* other)> OnCollisionExitCallback;
		void SetIsStatic(bool isStatic);
		void SetIsTrigger(bool isTrigger);
		void Translate(glm::vec3 translation);
	private:
		void SetUpRigidBody();
		BodyType type;
		btRigidBody* body;
		btMotionState* motionState;
		btSphereShape* sphereShape;
		btBoxShape* boxShape;
		btCylinderShape* cyliderShape;
		btCapsuleShape* capsuleShape;
		btTriangleMeshShape* meshShape;
		Gel::Mesh mesh;
		float mass;
		bool colliding;
		bool collisionEnter;
		RigidBodyComponent* currentOther;
		bool isStatic;
		bool isTrigger;
	};

}