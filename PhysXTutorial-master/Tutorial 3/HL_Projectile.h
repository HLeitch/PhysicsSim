#pragma once
#include "PhysicsEngine.h"
#include <PxPhysicsAPI.h>
namespace HL_PhysicsEngine
{
    class HL_Projectile :
        public DynamicActor
    {
    public:
        PxReal lifetime;
        
        HL_Projectile(PxVec3 location, PxVec3 direction);
    };
}