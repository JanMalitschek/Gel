#include "PhysicsEngine.h"

#include "RigidBodyComponent.h"

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
		world->stepSimulation(timeStep, 16);
	}

	void PhysicsEngine::AddRigidBody(btRigidBody* newBody) {
		PhysicsEngine::world->addRigidBody(newBody);
	}

	RaycastHitResult PhysicsEngine::RayCast(glm::vec3 origin, glm::vec3 direction, float distance) {
		btVector3 start = btVector3(origin.x, origin.y, origin.z);
		btVector3 end = start + btVector3(direction.x, direction.y, direction.z) * distance;
		btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
		world->rayTest(start, end, rayCallback);
		RaycastHitResult rayHit;
		if (rayCallback.hasHit()) {
			rayHit.hit = true;
			rayHit.hitPoint = glm::vec3(rayCallback.m_hitPointWorld.getX(), rayCallback.m_hitPointWorld.getY(), rayCallback.m_hitPointWorld.getZ());
			rayHit.hitNormal = glm::vec3(rayCallback.m_hitNormalWorld.getX(), rayCallback.m_hitNormalWorld.getY(), rayCallback.m_hitNormalWorld.getZ());
			rayHit.body = static_cast<RigidBodyComponent*>(rayCallback.m_collisionObject->getUserPointer());
		}
		else {
			rayHit.hit = false;
			rayHit.hitPoint = glm::vec3(0.0f, 0.0f, 0.0f);
			rayHit.hitNormal = glm::vec3(0.0f, 0.0f, 1.0f);
		}
		return rayHit;
	}

	void PhysicsEngine::CheckForCollision() {
		int numManifolds = world->getDispatcher()->getNumManifolds();
		for (int i = 0; i < numManifolds; i++) {
			btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* objA = contactManifold->getBody0();
			const btCollisionObject* objB = contactManifold->getBody1();

			Gel::RigidBodyComponent* compA = static_cast<Gel::RigidBodyComponent*>(objA->getUserPointer());
			Gel::RigidBodyComponent* compB = static_cast<Gel::RigidBodyComponent*>(objB->getUserPointer());

			int numContacts = contactManifold->getNumContacts();
			for (int j = 0; j < numContacts; j++) {
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				if (pt.getDistance() < 0.0f) {
					if (compA != nullptr) {
						compA->Colliding(compB);
					}
					if (compB != nullptr) {
						compB->Colliding(compA);
					}
				}
			}
		}
	}

	btVector3 PhysicsEngine::glmToBt(glm::vec3 vec) {
		return btVector3(vec.x, vec.y, vec.z);
	}

}
