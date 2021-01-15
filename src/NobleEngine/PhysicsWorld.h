#pragma once
#ifndef PHYSICSWORLD_H_
#define PHYSICSWORLD_H_

#include <memory>

#include <Bullet/btBulletDynamicsCommon.h>

namespace NobleEngine
{
	/**
	*Stores various options regarding the bullet physics.
	*/
	struct PhysicsWorld
	{
	private:
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicWorld;

		btAlignedObjectArray<btCollisionShape*> collisionShapes;

	public:
		/**
		*Creates a physics world object.
		*/
		static std::shared_ptr<PhysicsWorld> CreatePhysicsWorld();
		/**
		*Cleans up the physics world memory.
		*/
		void CleanupPhysicsWorld();
		/**
		*Adds a collider to the list of all colliders.
		*/
		void AddCollider(btCollisionShape* shape);
		/**
		*Adds a rigidbody to the physics world.
		*/
		void AddRigidbody(btRigidBody* body);
		/**
		*Steps the physics simulation by the amount.
		*/
		void StepSimulation(double amount);
	};
}

#endif