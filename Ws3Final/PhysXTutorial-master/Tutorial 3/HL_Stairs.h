#pragma once
#include "BasicActors.h"
namespace HL_PhysicsEngine
{
	class HL_Stairs{
	
	public:
		vector<StaticBox*> _stairs;

		HL_Stairs(PxVec3 start, PxVec3 end, PxReal width = 1., PxReal height = 1, PxReal Depth = 1.3);

	};
}
