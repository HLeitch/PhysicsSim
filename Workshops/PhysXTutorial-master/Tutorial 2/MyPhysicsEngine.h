#pragma once

#include "BasicActors.h"
#include "HL_RectEnclosure.h"
#include "HL_StaticEnclosure.h"
#include "HL_Projectile.h"
#include <PxPhysicsAPI.h>
#include <iostream>
#include <iomanip>


namespace HL_PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = { PxVec3(46.f / 255.f,9.f / 255.f,39.f / 255.f),PxVec3(217.f / 255.f,0.f / 255.f,0.f / 255.f),
		PxVec3(255.f / 255.f,45.f / 255.f,0.f / 255.f),PxVec3(255.f / 255.f,140.f / 255.f,54.f / 255.f),PxVec3(4.f / 255.f,117.f / 255.f,111.f / 255.f) };


	//pyramid vertices
	static PxVec3 pyramid_verts[] = { PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1) };

	static PxVec3 wedge_verts[] = { PxVec3(-1,0,1), PxVec3(1,0,1) , PxVec3(-1,0,-1) , PxVec3(-1,1,-1) , PxVec3(1,0,-1) , PxVec3(1,1,-1) };

	static PxU32 wedge_trigs[] = { 0,3,1,1,3,5,5,4,1,1,2,4,0,2,1,3,0,2,3,2,5,5,2,4 };
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = { 1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1 };

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box;

	public:
		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();

			GetMaterial()->setDynamicFriction(.4f);
			GetMaterial()->setStaticFriction(.5f);
			GetMaterial()->setRestitution(0.2f);

			plane = new Plane();
			Add(plane);

			/*box = new Box(PxTransform(PxVec3(0.f,10.f,.0f)));
			box->Color(232.0f,134.0f,247.0f);
			Add(box);


			Box* box1 = new Box(PxTransform(PxVec3(-3.f, 10.f, .0f)));
			box1->GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 10.f, .0f), PxQuat((0.25 * PxPi), PxVec3(0.f, 1.f, 1.f))));
			box1->Color(159.0f, 198.0f, 252.0f);
			Add(box1);
			box1->CreateShape(PxBoxGeometry(.5f,.5f,.5f), .3f);
			box1->GetShape(1)->setLocalPose(PxTransform(PxVec3(3.f, 0.f, 0.f)));



			Box* box2 = new Box(PxTransform(PxIdentity));
			box2->Color(252.0f, 240.0f, 109.0f);
			Add(box2);
			*/
			for (int i = 0; i < 18; i++)
			{
				float noise = ((float)(std::rand() % 1000) / 1000) - 0.5f;

				Box* rotBox = new Box(PxTransform(PxVec3(1, 0.6 + (1.1f * i), 1)), PxVec3(.5 - (0.02 * i)));
				//rotBox->GetShape()->setLocalPose(PxTransform(PxVec3(-0.5f, .5f, -10.f), PxQuat(20.f, PxVec3(1.f, 1.f, .0f))));
				rotBox->Color(color_palette[i % 5]);
				Add(rotBox);
			}

			/*capsuleCompound = new Capsule(PxTransform(PxVec3(-5.f, 10.f, 0.f)),PxVec2(0.1f,0.3f));
			capsuleCompound->GetShape(0)->setLocalPose(PxTransform(PxVec3(2.f, 0.f, .0f), PxQuat((0.5 * PxPi), PxVec3(0.f, 1.f, 1.f))));
			capsuleCompound->Color(color_palette[4]);


			capsuleCompound->CreateShape(PxCapsuleGeometry(0.1f,0.3f) , 1.0f);
			capsuleCompound->GetShape(1)->setLocalPose(PxTransform(PxVec3(-2.f, 0.f, 0.f)));

			capsuleCompound->CreateShape(capsuleCompound->GetShape(0)->getGeometry().any(), 1.0f);
			capsuleCompound->GetShape(2)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, 1.f)));

			capsuleCompound->CreateShape(capsuleCompound->GetShape(0)->getGeometry().any(), 1.0f);
			capsuleCompound->GetShape(3)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, -1.f)));
			*/

			/*	Add(capsuleCompound);
				capsuleCompound->SetKinematic(true);*/

				/*for (int i = 0; i < 1000; i++)
	{
		float noise = ((float)(std::rand() % 1000) / 500) - 0.5f;

		Sphere* sphere = new Sphere(PxTransform(PxVec3(0.f, 70.f + (i * 2), -10.f)), PxReal(.1f), PxReal(5.f));
		this->Add(sphere);

	}*/
	//HL_RectEnclosure* enclosure = new HL_RectEnclosure(PxTransform(PxVec3(20.f, 10.f, 20.f)));
	//Add(enclosure);

			HL_StaticEnclosure* statEnc = new HL_StaticEnclosure(10, 2, 10, 0.25, PxTransform(PxIdentity));
			statEnc->GetShape()->setLocalPose(PxTransform(PxVec3(0.f, .25f, 0.f), PxQuat(0.f, PxVec3(0, 0, 1.f))));
			Add(statEnc);
			statEnc->Color(color_palette[3]);

			//this pyramid is now a wedge
			Pyramid* pyramid = new Pyramid();
			pyramid->Color(color_palette[3]);
			pyramid->GetShape()->setLocalPose(PxTransform(PxVec3(3.f, 0.5f, 3.f), PxQuat((0.5 * PxPi), PxVec3(0, 1, 0))));
			Add(pyramid);



		}

		virtual void CustomInput(bool key_state[])
		{
			if (key_state['P'] == true)
			{
				HL_Projectile* proj = new HL_Projectile()
			}
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
		}
	};
}
