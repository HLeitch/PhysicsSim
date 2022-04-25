#include "Domino.h"
namespace HL_PhysicsEngine {
	HL_Domino::HL_Domino(PxTransform& pose, PxVec3 dims) :Box(pose, dominoDimensions, dominoDensity)
	{

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
			dominoesContained.push_back(newDomino);
			
		}

	}
}

