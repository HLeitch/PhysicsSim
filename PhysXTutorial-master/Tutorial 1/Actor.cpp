#include "Actor.h"
#include <vector>
namespace PhysicsEngine
{
	using namespace std;
	PxActor* Actor::Get()
	{
		return actor;
	}

	PxShape* Actor::GetShape(PxU32 index)
	{
		std::vector<PxShape*> shapes(((PxRigidActor*)actor)->getNbShapes());
		if (index < ((PxRigidActor*)actor)->getShapes((PxShape**)&shapes.front(), (PxU32)shapes.size()))
			return shapes[index];
		else
			return 0;
	}
}