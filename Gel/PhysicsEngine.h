#pragma once

#include "Core.h"

#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>

#include <glm\glm.hpp>
#include <stdio.h>
#include <iostream>

namespace Gel {

	enum BodyType {
		Sphere,
		Box
	};

	enum ForceType {
		Force,
		Impulse
	};

	struct GEL_API RaycastHitResult {
		bool hit;
		btRigidBody* body;
		glm::vec3 hitPoint;
		glm::vec3 hitNormal;
	};

	static class GEL_API PhysicsEngine {
	public:
		static void Init();
		static void Update(btScalar timeStep);
		static void AddRigidBody(btRigidBody* newBody);
		static RaycastHitResult RayCast(glm::vec3 origin, glm::vec3 direction, float distance);
		static void CheckForCollision();
	private:
		static btDynamicsWorld* world;
		static btDispatcher* dispatcher;
		static btCollisionConfiguration* collisionConfig;
		static btBroadphaseInterface* broadPhase;
		static btConstraintSolver* constraintSolver;
	};
}