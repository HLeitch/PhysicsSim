#pragma once
#include "BasicActors.h"
#include "HL_Materials.h"
namespace HL_PhysicsEngine
{

    static const PxVec3 dominoDimensions = PxVec3(0.2, 0.3, 0.06);
    static const PxReal dominoDensity = PxReal(2.f);
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


    class HL_Image
    {
    public:
        void AddToScene(Scene* scene);
        vector<HL_DominoContainer*> DominoContainersHeld;
        vector<Box*> turners;

        vector<bool> PixelValues = { 0,1,0,0,1,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,0,
0,1,1,1,1,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,0,
0,1,0,0,1,0,1,1,1,1 };

        void ApplyPixels(vector<bool> vals);

        HL_Image(PxVec3 position,PxVec3 dimensions,PxVec3 domDims = dominoDimensions);

    };


}
