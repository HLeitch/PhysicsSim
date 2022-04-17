
#include "HL_Projectile.h"

namespace HL_PhysicsEngine
{

	HL_PhysicsEngine::HL_Projectile::HL_Projectile(PxVec3 location, PxVec3 direction) :DynamicActor(PxTransform(location))
	{
		this->CreateShape(PxSphereGeometry(0.3), 3.f);
	};
}
