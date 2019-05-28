#include "RigidBodyComponent.h"

namespace Gel {

	RigidBodyComponent::RigidBodyComponent(Transform* parentTransform, BodyType type, float mass, Gel::Mesh mesh)
	{
		this->parentTransform = parentTransform;
		this->isActive = true;
		this->type = type;
		this->mass = mass;
		this->colliding = false;
		this->collisionEnter = false;
		OnCollisionEnterCallback = nullptr;
		OnCollisionStayCallback = nullptr;
		OnCollisionExitCallback = nullptr;
		currentOther = nullptr;
		this->isStatic = false;
		this->isTrigger = false;
		this->mesh = mesh;
		SetUpRigidBody();
	}

	RigidBodyComponent::RigidBodyComponent()
	{
		this->parentTransform = new Transform();
		this->isActive = true;
		this->type = BodyType::Sphere;
		this->mass = 1.0f;
		this->colliding = false;
		this->collisionEnter = false;
		SetUpRigidBody();
		OnCollisionEnterCallback = nullptr;
		OnCollisionStayCallback = nullptr;
		OnCollisionExitCallback = nullptr;
		currentOther = nullptr;
		this->isStatic = false;
		this->isTrigger = false;
	}

	void RigidBodyComponent::Update() {
		if (this->isActive) {
			btTransform t;
			this->body->getMotionState()->getWorldTransform(t);
			this->parentTransform->position.x = t.getOrigin().getX();
			this->parentTransform->position.y = t.getOrigin().getY();
			this->parentTransform->position.z = t.getOrigin().getZ();
			this->parentTransform->SetRotation(glm::quat(t.getRotation().getW(), t.getRotation().getX(), t.getRotation().getY(), t.getRotation().getZ()));

			//Collision Callbacks
			if (this->colliding) {
				if (OnCollisionStayCallback != nullptr)
					OnCollisionStayCallback(currentOther);
				if (!this->collisionEnter) {
					if (OnCollisionEnterCallback != nullptr)
						OnCollisionEnterCallback(currentOther);
				}
				this->collisionEnter = true;
			}
			else {
				if (this->collisionEnter) {
					if(OnCollisionExitCallback != nullptr)
						OnCollisionExitCallback(currentOther);
					this->collisionEnter = false;
				}
			}
			this->colliding = false;
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
		cyliderShape = new btCylinderShape(btVector3(0.5f, 0.5f, 0.5f));
		capsuleShape = new btCapsuleShape(1.0f, 4.0f);
		btVector3 inertia = btVector3(0.0f, 0.0f, 0.0f);
		switch (this->type) {
		case BodyType::Sphere:
			sphereShape->calculateLocalInertia(this->mass, inertia);
			sphereShape->setMargin(0.04f);
			this->body = new btRigidBody(this->mass, motionState, sphereShape, inertia);
			break;
		case BodyType::Box:
			boxShape->calculateLocalInertia(this->mass, inertia);
			boxShape->setMargin(0.04f);
			this->body = new btRigidBody(this->mass, motionState, boxShape, inertia);
			break;
		case BodyType::Cylinder:
			cyliderShape->calculateLocalInertia(this->mass, inertia);
			cyliderShape->setMargin(0.04f);
			this->body = new btRigidBody(this->mass, motionState, cyliderShape, inertia);
			break;
		case BodyType::Capsule:
			capsuleShape->calculateLocalInertia(this->mass, inertia);
			capsuleShape->setMargin(0.04f);
			this->body = new btRigidBody(this->mass, motionState, capsuleShape, inertia);
			break;
		case BodyType::TriangleMesh:
			this->mass = 0.0f;
			if (this->mesh.vertices.size() > 0) {
				btTriangleMesh* trimesh = new btTriangleMesh();
				for (int i = 0; i < this->mesh.indices.size(); i+=3) {
					trimesh->addTriangle(PhysicsEngine::glmToBt(this->mesh.vertices[this->mesh.indices[i]].Position),
										 PhysicsEngine::glmToBt(this->mesh.vertices[this->mesh.indices[i + 1]].Position),
										 PhysicsEngine::glmToBt(this->mesh.vertices[this->mesh.indices[i + 2]].Position));
				}
				meshShape = new btBvhTriangleMeshShape(trimesh, false);
				meshShape->calculateLocalInertia(this->mass, inertia);
				meshShape->setMargin(0.04f);
				this->body = new btRigidBody(this->mass, motionState, meshShape, inertia);
			}
			else {
				printf("No Mesh Provided!");
				sphereShape->calculateLocalInertia(this->mass, inertia);
				sphereShape->setMargin(0.04f);
				this->body = new btRigidBody(this->mass, motionState, sphereShape, inertia);
			}
			break;
		case BodyType::ConvexHull:
			if (this->mesh.vertices.size() > 0) {
				btConvexHullShape* hull = new btConvexHullShape();
				for (int i = 0; i < this->mesh.vertices.size(); i++) {
					hull->addPoint(PhysicsEngine::glmToBt(this->mesh.vertices[i].Position));
				}
				hull->calculateLocalInertia(this->mass, inertia);
				hull->setMargin(0.04f);
				this->body = new btRigidBody(this->mass, motionState, hull, inertia);
			}
			else {
				printf("No Mesh Provided!");
				sphereShape->calculateLocalInertia(this->mass, inertia);
				sphereShape->setMargin(0.04f);
				this->body = new btRigidBody(this->mass, motionState, sphereShape, inertia);
			}
			break;
		default:
			break;
		}
		this->body->setRestitution(0.0f);
		this->body->setFlags(this->body->getFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
		this->body->setUserPointer(this);
		if (this->mass <= 0.0f)
			this->isStatic = true;
		PhysicsEngine::AddRigidBody(this->body);
	}

	void RigidBodyComponent::SetSize(btVector3 size) {
		if (this->body->getCollisionShape()->getShapeType() == BOX_SHAPE_PROXYTYPE) {
			this->body->getCollisionShape()->setLocalScaling(size);
			this->body->getCollisionShape()->setMargin(0.04f);
		}
	}
	void RigidBodyComponent::SetRadius(btScalar radius) {
		if (this->body->getCollisionShape()->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
			this->body->getCollisionShape()->setLocalScaling(btVector3(radius, radius, radius));
			this->body->getCollisionShape()->setMargin(0.04f);
		}
	}
	void RigidBodyComponent::SetRadiusAndHeight(btScalar radius, btScalar height) {
		if (this->body->getCollisionShape()->getShapeType() == CYLINDER_SHAPE_PROXYTYPE) {
			this->body->setCollisionShape(new btCylinderShape(btVector3(radius, height / 2, radius)));
			this->body->getCollisionShape()->setMargin(0.04f);
		}
		else if (this->body->getCollisionShape()->getShapeType() == CAPSULE_SHAPE_PROXYTYPE) {
			this->body->setCollisionShape(new btCapsuleShape(radius, height));
			this->body->getCollisionShape()->setMargin(0.04f);
		}
	}

	void RigidBodyComponent::SetBounciness(btScalar bounciness)
	{
		this->body->setRestitution(bounciness);
	}

	void RigidBodyComponent::SetFriction(btScalar friction)
	{
		this->body->setFriction(friction);
	}

	void RigidBodyComponent::SetRollingFriction(btScalar rollingFriction)
	{
		this->body->setRollingFriction(rollingFriction);
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
		this->body->activate();
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
		this->body->activate();
	}

	void RigidBodyComponent::Colliding(RigidBodyComponent* other) {
		this->colliding = true;
		this->currentOther = other;
	}

	void RigidBodyComponent::SetIsStatic(bool isStatic) {
		this->isStatic = isStatic;
		int staticFlag = 0;
		if (this->isStatic) {
			btVector3 inertia;
			this->body->getCollisionShape()->calculateLocalInertia(0.0f, inertia);
			this->body->setMassProps(0.0f, inertia);
			staticFlag = btCollisionObject::CF_STATIC_OBJECT;
		}
		else {
			btVector3 inertia;
			this->body->getCollisionShape()->calculateLocalInertia(this->mass, inertia);
			this->body->setMassProps(this->mass, inertia);
		}

		int triggerFlag = 0;
		if (this->isTrigger)
			triggerFlag = btCollisionObject::CF_NO_CONTACT_RESPONSE;

		this->body->setCollisionFlags(staticFlag | triggerFlag);
	}

	void RigidBodyComponent::SetIsTrigger(bool isTrigger) {
		this->isTrigger = isTrigger;
		int triggerFlag = 0;
		int staticFlag = 0;
		if (this->isTrigger)
			triggerFlag = btCollisionObject::CF_NO_CONTACT_RESPONSE;
		if (this->isStatic)
			staticFlag = btCollisionObject::CF_STATIC_OBJECT;
		this->body->setCollisionFlags(staticFlag | triggerFlag);
	}

	void RigidBodyComponent::Translate(glm::vec3 translation) {
		this->body->translate(btVector3(translation.x, translation.y, translation.z));
		this->body->activate();
	}

}