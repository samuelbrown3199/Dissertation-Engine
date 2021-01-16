#pragma once
#ifndef PHYSICSBODY_H_
#define PHYSICSBODY_H_

#include "Component.h"

#include <iostream>

#include <Bullet/btBulletDynamicsCommon.h>

#include "Transform.h"
#include "Entity.h"
#include "PhysicsWorld.h"

namespace NobleEngine
{
	struct PhysicsBody : public Component<PhysicsBody> 
	{
	private:
		std::shared_ptr<Transform> transform;
	public:

		~PhysicsBody()
		{
			Application::GetPhysicsWorld()->RemoveRigidbody(rigidBody);
			delete rigidBody;
			delete shape;
		}

		enum ColliderShape
		{
			box,
			sphere
		};
		/**
		*Used to detemine the shape of the collider.
		*/
		ColliderShape colliderShape;
		/**
		*Stores a collider shape pointer.
		*/
		btCollisionShape* shape;
		/**
		*Stores the rigidbody transform within the physics simulation.
		*/
		btTransform bodyTransform;
		/**
		*Stores the rigidbody mass.
		*/
		btScalar mass;
		/**
		*Stores a pointer to the rigidbody.
		*/
		btRigidBody* rigidBody;

		template<typename ... Args>
		void OnInitialize(ColliderShape _shape, btScalar _mass)
		{
			transform = GetEntity()->GetComponent<Transform>();
			colliderShape = _shape;

			switch (colliderShape)
			{
			case box:
				shape = new btBoxShape(btVector3(transform->scale.x, transform->scale.y, transform->scale.z));
				break;
			case sphere:
				shape = new btSphereShape(transform->scale.x);
				break;
			}
			Application::GetPhysicsWorld()->AddCollider(shape);

			bodyTransform.setOrigin(btVector3(transform->position.x, transform->position.y, transform->position.z));
			bodyTransform.setRotation(btQuaternion(transform->rotation.x, transform->rotation.y, transform->rotation.z));

			mass = _mass;
			btVector3 localInertia(0, 0, 0);
			bool isDynamic = (mass != 0.f);
			if (isDynamic)
			{
				shape->calculateLocalInertia(mass, localInertia);
			}
			btDefaultMotionState* motionState = new btDefaultMotionState(bodyTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
			rbInfo.m_linearDamping = .2f;
			rbInfo.m_angularDamping = .2f;
			rbInfo.m_restitution = 0.35;

			rigidBody = new btRigidBody(rbInfo);
			rigidBody->setFriction(.5f);
			rigidBody->setRollingFriction(.5f);

			Application::GetPhysicsWorld()->AddRigidbody(rigidBody);
		}
	};
}

#endif