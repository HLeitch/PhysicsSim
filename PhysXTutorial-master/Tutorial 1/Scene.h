#pragma once
#include "PxPhysicsAPI.h"
#include "Actor.h"
namespace PhysicsEngine
{
	using namespace physx;
		///Generic scene class
		class Scene
		{
		protected:
			//a PhysX scene object
			PxScene* px_scene;

		public:
			///Init the scene
			void Init();

			///User defined initialisation
			virtual void CustomInit() {}

			///Perform a single simulation step
			void Update(PxReal dt);

			///User defined update step
			virtual void CustomUpdate() {}

			///Add actors
			void Add(Actor* actor);

			///Get the PxScene object
			PxScene* Get();

			///Reset the scene
			void Reset();
		};
}
