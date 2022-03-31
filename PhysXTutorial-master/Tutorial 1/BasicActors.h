#pragma once

#include "PhysicsEngine.h"
#include "DynamicActor.h"

namespace PhysicsEngine
{
	///Plane class
	class Plane : public StaticActor
	{
	public:
		//A plane with default paramters: XZ plane centred at (0,0,0)
		Plane(PxVec3 normal = PxVec3(0.f, 1.f, 0.f), PxReal distance = 0.f)
			: StaticActor(PxTransformFromPlaneEquation(PxPlane(normal, distance)))
		{
			CreateShape(PxPlaneGeometry());
		}
	};

	///Box class
	class Box : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Box(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}

	};
	class StaticBox : public StaticActor
	{
		//a Box with default parameters:
// - pose in 0,0,0
// - dimensions: 1m x 1m x 1m
// - denisty: 1kg/m^3
	public:
		StaticBox(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class Capsule : public DynamicActor
	{
	public:
		Capsule(const PxTransform& pose, PxReal radius, PxReal halfHeight, PxReal density);
	};

	class Sphere : public DynamicActor
	{
	public:
		Sphere(const PxTransform& pose, PxReal radius, PxReal density);
	};
}
