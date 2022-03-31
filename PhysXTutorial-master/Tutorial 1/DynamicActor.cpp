#include "DynamicActor.h"
#include "PxPhysicsAPI.h"
#include "PhysicsEngine.h"

namespace PhysicsEngine
{


	void DynamicActor::CreateShape(const PxGeometry& geometry, PxReal density)
	{
		PxShape* shape = ((PxRigidDynamic*)actor)->createShape(geometry, *GetMaterial());
		PxRigidBodyExt::updateMassAndInertia(*(PxRigidDynamic*)actor, density);
	}

	DynamicActor::DynamicActor(const PxTransform& pose) : Actor()
	{
		actor = (PxActor*)GetPhysics()->createRigidDynamic(pose);
	}
}