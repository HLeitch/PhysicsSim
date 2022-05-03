#pragma once
#include "BasicActors.h"
#include "HL_Materials.h"
namespace HL_PhysicsEngine
{

    static const PxVec3 dominoDimensions = PxVec3(0.4, 0.6, 0.1);
    static const PxReal dominoDensity = PxReal(3.f);
    class HL_Domino :
        public Box
    {


    public:
        HL_Domino(PxTransform& pose = PxTransform(PxIdentity), PxVec3 dims = dominoDimensions);

    };

    class HL_DominoContainer
    {


    public:
        vector<HL_Domino*> dominoesContained;
        HL_DominoContainer(PxVec3 start, PxVec3 end, PxVec3 dominoDimensions = dominoDimensions);
    };

}
