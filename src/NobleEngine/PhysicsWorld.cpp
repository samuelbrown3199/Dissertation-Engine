#include "PhysicsWorld.h"

namespace NobleEngine
{
	std::shared_ptr<PhysicsWorld> PhysicsWorld::CreatePhysicsWorld()
	{
		std::shared_ptr<PhysicsWorld> rtn = std::make_shared<PhysicsWorld>();

		rtn->collisionConfiguration = new btDefaultCollisionConfiguration();
		rtn->dispatcher = new btCollisionDispatcher(rtn->collisionConfiguration);
		rtn->overlappingPairCache = new btDbvtBroadphase();
		rtn->solver = new btSequentialImpulseConstraintSolver;
		rtn->dynamicWorld = new btDiscreteDynamicsWorld(rtn->dispatcher, rtn->overlappingPairCache, rtn->solver, rtn->collisionConfiguration);
		rtn->dynamicWorld->setGravity(btVector3(0, -9.80, 0));

		return rtn;
	}

	void PhysicsWorld::CleanupPhysicsWorld()
	{
		delete dynamicWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
	}

	void PhysicsWorld::AddCollider(btCollisionShape* shape)
	{
		collisionShapes.push_back(shape);
	}
	void PhysicsWorld::AddRigidbody(btRigidBody* body)
	{
		dynamicWorld->addRigidBody(body);
	}
	void PhysicsWorld::RemoveRigidbody(btRigidBody* body)
	{
		dynamicWorld->removeRigidBody(body);
	}
	void PhysicsWorld::StepSimulation(double amount)
	{
		dynamicWorld->stepSimulation(amount);
	}
}