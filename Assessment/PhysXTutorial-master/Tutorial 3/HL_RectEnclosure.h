#pragma once
#include "PhysicsEngine.h"

namespace HL_PhysicsEngine
{
    class HL_RectEnclosure :
        public DynamicActor
    {
        public:
        HL_RectEnclosure(PxTransform pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(10.f, 10.f, 10.f), PxReal wallThickness = PxReal(1.f), PxReal density = PxReal(1.f));

    };
}


