#pragma once
#include "BasicActors.h"
#include <PxPhysicsAPI.h>

namespace HL_PhysicsEngine
{

    using namespace physx;
    static const PxU32 enclosureTris[] = { 0,2,1,1,2,3,4,5,0,0,5,2,1,3,6,6,3,7,4,7,5,6,4,7,2,5,3,3,5,7,10,11,12,11,13,12,11,15,13,14,15,11,10,12,16,16,12,17,16,17,14,14,17,15,17,12,15,15,12,13,4,0,10,16,4,10,10,0,1,10,1,11,11,1,14,14,1,6,6,16,14,6,4,16 };

    class HL_StaticEnclosure :
        public TriangleMesh
    {
    public:
        HL_StaticEnclosure(PxReal width, PxReal height, PxReal depth, PxReal wallThck, const PxTransform& pose );
        ~HL_StaticEnclosure();
    private:
        static std::vector<PxVec3>* SetVerts(PxReal width, PxReal height, PxReal depth, PxReal wallThck);
        std::vector<PxVec3>* GetVerts(PxReal width = 10, PxReal height = 10, PxReal depth = 10, PxReal wallThck = 1);
        std::vector<PxVec3>* _scaledVerts = nullptr;
   


    };

    class HL_DynamicEnclosure :public ConvexMesh
    {
    public:
        HL_DynamicEnclosure(PxReal width, PxReal height, PxReal depth, PxReal wallThck, const PxTransform& pose = PxTransform(PxIdentity),PxReal density = PxReal(1.f));

    private:
        static std::vector<PxVec3>* SetVerts(PxReal width, PxReal height, PxReal depth, PxReal wallThck);
        std::vector<PxVec3>* GetVerts(PxReal width = 10, PxReal height = 10, PxReal depth = 10, PxReal wallThck = 1);
        std::vector<PxVec3>* _scaledVerts = nullptr;


    };
}
