#pragma once

#pragma once

#include <vector>
#include "PxPhysicsAPI.h"
#include "Exception.h"
#include "Actor.h"
#include <string>

namespace PhysicsEngine
{
	using namespace physx;
	using namespace std;
	
	///Initialise PhysX framework
	void PxInit();

	///Release PhysX resources
	void PxRelease();

	///Get the PxPhysics object
	PxPhysics* GetPhysics();

	///Get the specified material
	PxMaterial* GetMaterial(PxU32 index=0);

	///Create a new material
	PxMaterial* CreateMaterial(PxReal sf=.0f, PxReal df=.0f, PxReal cr=.0f);

	class StaticActor : public Actor
	{
	public:
		StaticActor(const PxTransform& pose);

		void CreateShape(const PxGeometry& geometry, PxReal density=0.f);
	};

	
}

