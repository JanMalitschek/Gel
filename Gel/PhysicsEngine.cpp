#include "PhysicsEngine.h"

namespace Gel{

	btDynamicsWorld* PhysicsEngine::world = nullptr;
	btDispatcher* PhysicsEngine::dispatcher = nullptr;
	btCollisionConfiguration* PhysicsEngine::collisionConfig = nullptr;
	btBroadphaseInterface* PhysicsEngine::broadPhase = nullptr;
	btConstraintSolver* PhysicsEngine::constraintSolver = nullptr;
	
	
	void PhysicsEngine::Init() {
		PhysicsEngine::collisionConfig = new btDefaultCollisionConfiguration();
		PhysicsEngine::dispatcher = new btCollisionDispatcher(PhysicsEngine::collisionConfig);
		PhysicsEngine::broadPhase = new btDbvtBroadphase();
		PhysicsEngine::constraintSolver = new btSequentialImpulseConstraintSolver();
		PhysicsEngine::world = new btDiscreteDynamicsWorld(PhysicsEngine::dispatcher,
			PhysicsEngine::broadPhase,
			PhysicsEngine::constraintSolver,
			PhysicsEngine::collisionConfig);
		PhysicsEngine::world->setGravity(btVector3(0.0f, -9.1f, 0.0f));
	}
	
	void PhysicsEngine::Update(btScalar timeStep) {
		world->stepSimulation(timeStep);
	}

	void PhysicsEngine::AddRigidBody(btRigidBody* newBody) {
		PhysicsEngine::world->addRigidBody(newBody);
	}

}
