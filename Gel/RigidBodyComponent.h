#pragma once

#include "Core.h"
#include "PhysicsEngine.h"
#include "Component.h"

namespace Gel {

	class GEL_API RigidBodyComponent : public Component
	{
	public:
		RigidBodyComponent(Transform* parentTransform, BodyType type, float mass);
		RigidBodyComponent();
		void Update();
		void SetSize(btVector3 size);
		void SetRadius(btScalar radius);
		void AddForce(glm::vec3 force, ForceType forceType);
		void AddTorque(glm::vec3 torque, ForceType torqueType);
	private:
		void SetUpRigidBody();
		BodyType type;
		btRigidBody* body;
		btMotionState* motionState;
		btSphereShape* sphereShape;
		btBoxShape* boxShape;
		float mass;
	};

}