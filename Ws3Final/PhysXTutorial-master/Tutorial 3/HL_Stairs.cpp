#include "HL_Stairs.h"

HL_PhysicsEngine::HL_Stairs::HL_Stairs(PxVec3 start, PxVec3 end, PxReal width, PxReal height, PxReal depth)
{
	PxVec3 vectorDistance = end - start;

	PxReal numDominoes = PxAbs(vectorDistance.y)/(height*2);

	PxVec3 distanceIncrement = vectorDistance / numDominoes;

	for (int i = 0; i < numDominoes; i++)
	{
		StaticBox* _box = new StaticBox(PxTransform(start + (distanceIncrement * i)), PxVec3(width, height, depth));
		_box->Get()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

		//Rotate in y axis to point domino toward end point. 
			///angle = Tan(dX/dZ)
		PxReal angle = PxTan((vectorDistance.x / vectorDistance.z));
		if (isnan(angle))
		{
			angle = 0.5 * PxPi;
		}
		PxVec3 axisOfRotation = PxVec3(0, 1, 0);

		//rotate domino
		_box->GetShape()->setLocalPose(PxTransform(_box->GetShape()->getLocalPose().p, PxQuat(angle, axisOfRotation)));

		_stairs.push_back(_box);
	}


}
