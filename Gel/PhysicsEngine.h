#pragma once

#include "Core.h"

#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>

namespace Gel {

	enum BodyType {
		Sphere,
		Box
	};

	enum ForceType {
		Force,
		Impulse
	};

	static class GEL_API PhysicsEngine {
	public:
		static void Init();
		static void Update(btScalar timeStep);
		static void AddRigidBody(btRigidBody* newBody);
	private:
		static btDynamicsWorld* world;
		static btDispatcher* dispatcher;
		static btCollisionConfiguration* collisionConfig;
		static btBroadphaseInterface* broadPhase;
		static btConstraintSolver* constraintSolver;
	};
}