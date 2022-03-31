#pragma once
#include "PxPhysicsAPI.h"
	///Abstract Actor class
	///Inherit from this class to create your own actors
namespace PhysicsEngine
{
	using namespace physx;
	class Actor
	{
	protected:
		PxActor* actor;

	public:
		///Constructor
		Actor()
			: actor(0)
		{
		}

		PxActor* Get();

		PxShape* GetShape(PxU32 index = 0);

		virtual void CreateShape(const PxGeometry& geometry, PxReal density) {}
	};
}
