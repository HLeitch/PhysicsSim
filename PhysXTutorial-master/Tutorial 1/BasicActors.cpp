#include "BasicActors.h"

namespace PhysicsEngine
{
	Capsule::Capsule(const PxTransform& pose = PxTransform(PxIdentity), PxReal radius = 1.f, PxReal halfHeight = 1.f, PxReal density = 1.f) : DynamicActor(pose)
	{
		CreateShape(PxCapsuleGeometry(radius, halfHeight), density);
	}

	Sphere::Sphere(const PxTransform& pose = PxTransform(PxIdentity), PxReal radius = 1.f, PxReal density = 1.f) : DynamicActor(pose)
	{
		CreateShape(PxSphereGeometry(radius), density);
	}
}