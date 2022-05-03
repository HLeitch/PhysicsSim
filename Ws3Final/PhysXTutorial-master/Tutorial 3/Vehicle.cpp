#include "Vehicle.h"
#include "HL_StaticEnclosure.h"

HL_PhysicsEngine::Vehicle::Vehicle(PxTransform pose)
{
	HL_StaticEnclosure* body = new HL_StaticEnclosure(3, 2, 4, 0.3, PxTransform(PxVec3(0.f, 2, -5)));

}
