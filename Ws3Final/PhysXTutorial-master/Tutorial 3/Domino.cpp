#include "Domino.h"
namespace HL_PhysicsEngine {
	HL_Domino::HL_Domino(PxTransform& pose, PxVec3 dims) :Box(pose, dominoDimensions, dominoDensity)
	{
		PxMaterial* mat = GetMaterial(HL_Materials::plastic);
		GetShape()->setMaterials(& mat,1);
	}

	HL_DominoContainer::HL_DominoContainer(PxVec3 start, PxVec3 end, PxVec3 dominoDimensions)
	{
		PxVec3 vectorDistance = (end - start);

		PxReal distance = vectorDistance.magnitude();
		PxVec3 direction = vectorDistance.getNormalized();
		

		//distance between dominoes is the width plus some of the height. recommendation found from a website.
		PxReal numDominos = distance / (dominoDimensions.z + (1.2f * dominoDimensions.y));

		//The distance between each domino
		PxVec3 distanceIncrement = (direction * distance) / numDominos;

		for (int i = 0; i < numDominos; i++)
		{
			//position the domino along a line connecting the start and end points
			HL_Domino* newDomino = new HL_Domino(PxTransform(start + (distanceIncrement * i)));

			//Rotate in y axis to point domino toward end point. 
			///angle = Tan(dX/dZ)
			PxReal angle = PxTan((vectorDistance.x / vectorDistance.z));
			if (isnan(angle))
			{
				angle = 0.5*PxPi;
			}
			PxVec3 axisOfRotation = PxVec3(0, 1, 0);

			//rotate domino
			newDomino->GetShape()->setLocalPose(PxTransform(newDomino->GetShape()->getLocalPose().p,PxQuat(angle, axisOfRotation)));


			dominoesContained.push_back(newDomino);
			
		}

	}
}

