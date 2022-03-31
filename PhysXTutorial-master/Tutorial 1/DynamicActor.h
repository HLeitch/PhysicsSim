#pragma once
#include "Actor.h"
namespace PhysicsEngine
{
    class DynamicActor :
        public Actor
    {
    public:
        DynamicActor(const PxTransform& pose);

        void CreateShape(const PxGeometry& geometry, PxReal density);
    };
}
