
#include "HL_Projectile.h"

namespace HL_PhysicsEngine
{
	//Do NOT use, find a way to add to scene in init of projectile
	void HL_Projectile::fireProjectile(PxVec3 direction, PxReal force)
	{ 
		PxRigidBody* rb = this->Get()->is<PxRigidBody>();
		rb->addForce(direction * force, PxForceMode::eVELOCITY_CHANGE);

	}
	HL_PhysicsEngine::HL_Projectile::HL_Projectile(PxVec3 location, PxVec3 direction, PxReal force) :DynamicActor(PxTransform(location))
	{
		this->CreateShape(PxSphereGeometry(0.3), 3.f);
		this->lifetime = PxReal(5.f);
		this->fireProjectile(direction, force);
		
	};

	HL_PhysicsEngine::HL_Projectile::HL_Projectile(PxVec3 location) : DynamicActor(PxTransform(location))
	{
		this->CreateShape(PxSphereGeometry(0.3), 1.f);
	};
}
