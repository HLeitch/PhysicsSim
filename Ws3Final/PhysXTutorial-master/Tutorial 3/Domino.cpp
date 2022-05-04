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

		for (int i = 0; i <= numDominos; i++)
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

	void HL_Image::AddToScene(Scene* scene)
	{
		for (HL_DominoContainer* cont : this->DominoContainersHeld)
		{
			for (HL_Domino* dom : cont->dominoesContained)
			{
				scene->Add(dom);
			}
		}


		for (Box* turner : turners)
		{
			scene->Add(turner);
		}
		ApplyPixels(PixelValues);
	}

	void HL_Image::ApplyPixels(vector<bool> vals)
	{
		int domPerRow = DominoContainersHeld[0]->dominoesContained.size();
		float domPerPix =(float) domPerRow / sqrt(PixelValues.size());
		float rowPerPix = (float)(DominoContainersHeld.size() + 1) / sqrt(PixelValues.size());

		for (int row = 0; row < DominoContainersHeld.size(); row++)
		{
			int currentPixRow = row / rowPerPix;
			for (int col = 0; col < domPerRow; col++)
			{
				int currentPixCol = col / domPerPix;

				int pixIndex = (currentPixRow * sqrt(PixelValues.size()) + currentPixCol);

				//assign the current domino the colour of the pixel it represents
				HL_Domino* currentDom = DominoContainersHeld[row]->dominoesContained[col];
				if (vals[pixIndex])
				{
					currentDom->Color(PxVec3(0, 0, 0));
				}
				else
				{
					currentDom->Color(PxVec3(1, 1, 1));
				}

			}


		}
	}

	HL_Image::HL_Image(PxVec3 position, PxVec3 dimensions, PxVec3 domDims)
	{
		//dominos are twice their dimensions
		int numRows = 2*dimensions.z / (3*domDims.x);

		for (int i = 0; i < numRows; i++)
		{
			HL_DominoContainer* newCont = new HL_DominoContainer(PxVec3(position.x - dimensions.x, position.y, position.z -dimensions.z + (3 * domDims.x*i)), PxVec3(position.x + dimensions.x, position.y, position.z-dimensions.z + (3 * domDims.x*i)),domDims);

			DominoContainersHeld.push_back(newCont);
		}

		//flips after each loop to change the side on which the seesaw is placed
		bool altSide = false;
		for (int i = 0; i < numRows - 1; i++)
		{
			float xpos = dimensions.x+(domDims.y*3/5);
			if (altSide)
			{
				xpos = -xpos;
			}

			float zpos = position.z -dimensions.z + ((1.5*domDims.x)+ (3) * domDims.x*((i)));

			Box* turner = new Box(PxTransform(position.x + xpos, position.y + domDims.y, zpos),PxVec3(domDims.z/5,domDims.y/5, domDims.x*1.8f),2.0f);

			RevoluteJoint(nullptr, PxTransform(position.x + xpos, position.y + domDims.y, zpos,PxQuat(PxPi/2,PxVec3(0,0,1).getNormalized())), turner, PxTransform(PxIdentity));

			turners.push_back(turner);

			altSide = !altSide;
		}

	}

}

