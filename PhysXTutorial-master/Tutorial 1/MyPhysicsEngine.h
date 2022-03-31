#pragma once

#include "BasicActors.h"
#include <random>
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;

	///A custom scene class
	class MyScene : public Scene
	{
		Plane* bottomPlane;
		Box* box;

	public:
		//Custom scene initialisation
		virtual void CustomInit() 
		{
			GetMaterial()->setDynamicFriction(.6f);
			GetMaterial()->setRestitution(0.1f);

			bottomPlane = new Plane();
			Add(bottomPlane);

			StaticBox* wall1 = new StaticBox(PxTransform(PxVec3(10.f, 0.f, 0.f)),PxVec3(0.f,10.f,10.f));
			Add(wall1);

			StaticBox* wall2 = new StaticBox(PxTransform(PxVec3(-10.f, 0.f, 0.f)), PxVec3(0.f, 10.f, 10.f));
			Add(wall2);

			StaticBox* wall3 = new StaticBox(PxTransform(PxVec3(0.f, 0.f, 10.f)), PxVec3(10.f, 10.f, 0.f));
			Add(wall3);

			StaticBox* wall4 = new StaticBox(PxTransform(PxVec3(0.f, 0.f, -10.f)), PxVec3(10.f, 10.f, 0.f));
			Add(wall4);

			box = new Box(PxTransform(PxVec3(0.f,10.f,0.f)));
			Add(box);

			Box* box2 = new Box(PxTransform(PxVec3(0.f, 100.f, 0.f)));
			this->Add(box2);

			Box* box3 = new Box(PxTransform(PxVec3(3.f, 3.f, 0.f)));
			this->Add(box3);

			Box* box4 = new Box(PxTransform(PxVec3(3.f, 67.f, 0.f)));
			this->Add(box4);

			Capsule* box5 = new Capsule(PxTransform(PxVec3(6.f, 12.f, 0.f),PxQuat(90.0f,PxVec3(0.f,0.f,1.f))), PxReal(0.5f), PxReal(1.5f), PxReal(2.3f));
			this->Add(box5);

			Capsule* box6 = new Capsule(PxTransform(PxVec3(6.f, 123.f, 0.f)),PxReal(0.5f),PxReal(1.5f),PxReal(2.3f));
			this->Add(box6);

			for (int i = 0; i < 1000; i++)
			{
				float noise = ((float)(std::rand() % 1000) / 1000) - 0.5f;

				Sphere* sphere = new Sphere(PxTransform(PxVec3(2 + noise, 30.f + (i*2), 0.f)), PxReal(0.2f), PxReal(1.f));
				this->Add(sphere);
			}
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			//get position and velocity of the px_actor
			
			//note that the Get() function returns PxActor* only and therefore
			//to be able to access methods from the inherited classess (e.g. PxRigidDynamic)
			//we need to convert the pointer from PxActor* to PxRigidDynamic*
			
			PxRigidDynamic* px_actor = (PxRigidDynamic*)box->Get();
			PxVec3 position = px_actor->getGlobalPose().p;
			PxVec3 velocity = px_actor->getLinearVelocity();
			
			//'visualise' position and velocity of the box
			cout << setiosflags(ios::fixed) << setprecision(2) << "x=" << position.x << 
				", y=" << position.y << ", z=" << position.z << ",  ";
			cout << setiosflags(ios::fixed) << setprecision(2) << "vx=" << velocity.x << 
				", vy=" << velocity.y << ", vz=" << velocity.z << endl;
		}
	};
}
