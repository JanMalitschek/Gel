#include "RigidBodyComponent.h"

namespace Gel {

	RigidBodyComponent::RigidBodyComponent(Transform* parentTransform, BodyType type, float mass)
	{
		this->parentTransform = parentTransform;
		this->isActive = true;
		this->type = type;
		this->mass = mass;
		SetUpRigidBody();
	}

	RigidBodyComponent::RigidBodyComponent()
	{
		this->parentTransform = new Transform();
		this->isActive = true;
		this->type = BodyType::Sphere;
		this->mass = 1.0f;
		SetUpRigidBody();
	}

	void RigidBodyComponent::Update() {
		if (this->isActive) {
			btTransform t;
			this->body->getMotionState()->getWorldTransform(t);
			this->parentTransform->position.x = t.getOrigin().getX();
			this->parentTransform->position.y = t.getOrigin().getY();
			this->parentTransform->position.z = t.getOrigin().getZ();
			this->parentTransform->SetRotation(glm::quat(t.getRotation().getW(), t.getRotation().getX(), t.getRotation().getY(), t.getRotation().getZ()));
		}
	}

	void RigidBodyComponent::SetUpRigidBody() {
		btTransform t;
		t.setIdentity();
		t.setRotation(btQuaternion(parentTransform->rotation.x, parentTransform->rotation.y, parentTransform->rotation.z, parentTransform->rotation.w));
		t.setOrigin(btVector3(parentTransform->position.x, parentTransform->position.y, parentTransform->position.z));
		motionState = new btDefaultMotionState(t);
		sphereShape = new btSphereShape(1.0f);
		boxShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
		btVector3 inertia = btVector3(0.0f, 0.0f, 0.0f);
		switch (this->type) {
		case BodyType::Sphere:
			sphereShape->calculateLocalInertia(this->mass, inertia);
			this->body = new btRigidBody(this->mass, motionState, sphereShape, inertia);
			break;
		case BodyType::Box:
			boxShape->calculateLocalInertia(this->mass, inertia);
			this->body = new btRigidBody(this->mass, motionState, boxShape, inertia);
			break;
		default:
			break;
		}
		PhysicsEngine::AddRigidBody(this->body);
	}

	void RigidBodyComponent::SetSize(btVector3 size) {
		if (this->body->getCollisionShape()->getShapeType() == BOX_SHAPE_PROXYTYPE) {
			this->body->getCollisionShape()->setLocalScaling(size);
		}
	}
	void RigidBodyComponent::SetRadius(btScalar radius) {
		if (this->body->getCollisionShape()->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
			this->body->getCollisionShape()->setLocalScaling(btVector3(radius, radius, radius));
		}
	}

	void RigidBodyComponent::AddForce(glm::vec3 force, ForceType forceType) {
		switch (forceType) {
		case ForceType::Force:
			this->body->applyCentralForce(btVector3(force.x, force.y, force.z));
			break;
		case ForceType::Impulse:
			this->body->applyCentralImpulse(btVector3(force.x, force.y, force.z));
			break;
		default:
			break;
		}
	}
	void RigidBodyComponent::AddTorque(glm::vec3 torque, ForceType torqueType) {
		switch (torqueType) {
		case ForceType::Force:
			this->body->applyTorque(btVector3(torque.x, torque.y, torque.z));
			break;
		case ForceType::Impulse:
			this->body->applyTorqueImpulse(btVector3(torque.x, torque.y, torque.z));
			break;
		default:
			break;
		}
	}

}