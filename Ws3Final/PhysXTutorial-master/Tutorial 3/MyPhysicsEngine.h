#pragma once

#include "BasicActors.h"
#include "HL_Projectile.h"
#include "HL_Events.h"
#include <iostream>
#include <iomanip>
#include "KeyState.h"
#include "Domino.h"
#include "HL_StaticEnclosure.h"
#include "HL_Stairs.h"
#include "HL_Materials.h"

namespace HL_PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

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

	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0		= (1 << 0),
			ACTOR1		= (1 << 1),
			ACTOR2		= (1 << 2)
			//add more if you need
		};
	};

	///An example class showing the use of springs (distance joints).
	///Trampoline has been modified to have a static base.
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		Box* botto;
		StaticBox* bottom;

	public: 
		Box* top;
		Trampoline(const PxVec3& dimensions=PxVec3(1.f,1.f,1.f), PxReal stiffness=1.f, PxReal damping=1.f)
		{
			PxReal thickness = .1f;
			bottom = new StaticBox(PxTransform(PxVec3(0.f,thickness,0.f)),PxVec3(dimensions.x,thickness,dimensions.z));
			top = new Box(PxTransform(PxVec3(0.f,dimensions.y+thickness,0.f)),PxVec3(dimensions.x,thickness,dimensions.z));
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,-dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,-dimensions.z)));


			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}

		Trampoline(const PxVec3& position = PxVec3(0.f, 0.f, 0.f), const PxVec3& dimensions = PxVec3(1.f, 1.f, 1.f), PxReal stiffness = 1.f, PxReal damping = 1.f)
		{
			PxReal thickness = .1f;
			bottom = new StaticBox(PxTransform(PxVec3(0.f + position.x, thickness + position.y, 0.f + position.z)), PxVec3(dimensions.x, thickness, dimensions.z));
			top = new Box(PxTransform(PxVec3(0.f + position.x, dimensions.y + thickness + position.y, 0.f + position.z)), PxVec3(dimensions.x, thickness, dimensions.z));
			PxMaterial* trampMat = GetMaterial(PxU32(HL_Materials::basic));
			top->GetShape()->setMaterials( &trampMat,1);
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, -dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, -dimensions.z)));

			//PxPrismaticJointCreate(*GetPhysics(), bottom->GetShape()->getActor(), PxTransform(PxQuat(0, PxVec3(0.f, 1.f, 0.0f).getNormalized())), top->GetShape()->getActor(), PxTransform(0.f, dimensions.y + thickness, 0.f));

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;

		Scene* _Gscene = nullptr;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						//printf("Touch Count = ");
						PxActor* otherActor = pairs[i].otherActor;

						//BE WARNED CAN RETURN NULL IF NO RIGID BODY
						PxRigidBody* otherActorRB = pairs[i].otherActor->is<PxRigidBody>();
						HL_ADDFORCEEVENT* forceEvnt = new HL_ADDFORCEEVENT(otherActorRB);
						HL_Events::AddEvent(forceEvnt);

						PxShape* shapepointerpointer = nullptr;
						otherActorRB->getShapes(&shapepointerpointer, 1);
						PxShape* shapePointer = shapepointerpointer;

						if (shapePointer->getGeometryType() == PxGeometryType::eSPHERE) {
							printf("Sphere detected in hitbox");
						}

						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cout << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					//cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					//cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
#if PX_PHYSICS_VERSION >= 0x304000
		virtual void onAdvance(const PxRigidBody *const *bodyBuffer, const PxTransform *poseBuffer, const PxU32 count) {}
#endif
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
//		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box, * box2;

		Sphere* sphere;

		MySimulationEventCallback* my_callback;
		
	public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene() {};

		PxVec3 camPos;
		PxVec3 camDir;

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
			HL_MaterialsObject* _materials = new HL_MaterialsObject();

			/*GetMaterial()->setDynamicFriction(.1f);
			GetMaterial()->setStaticFriction(0.5f);
			GetMaterial()->setRestitution(0.4f);*/

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);
			my_callback->_Gscene = this;

			plane = new Plane();
			plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
			plane->Material(GetMaterial(HL_Materials::wood), 0);
			Add(plane);

			box = new Box(PxTransform(PxVec3(.0f, 1.f, .0f)), PxVec3(0.5f, 0.5f, 0.5f), 1.f);
			box->Color(color_palette[3]);

			box2 = new Box(PxTransform(PxVec3(.0f, 13.f, .0f)), PxVec3(0.5f, 0.5f, 0.5f), 1.f);
			box2->Color(color_palette[4]);
			//set collision filter flags
			//box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);
			//use | operator to combine more actors e.g.
			//box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1 | FilterGroup::ACTOR2);
			//don't forget to set your flags for the matching actor as well, e.g.:
			 //box2->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
			box->Name("Box1");
			Add(box);
			//Add(box2);



			//JOINTS AND MOTORS
			//
			////joint two boxes together
			////the joint is fixed to the centre of the first box, oriented by 90 degrees around the Y axis
			////and has the second object attached 5 meters away along the Y axis from the first object.
			///*PxQuat revoluteAngle = PxQuat(0 / 2, PxVec3(0.f, 1.f, .0f).getNormalized());
			//RevoluteJoint* joint  = new RevoluteJoint(nullptr, PxTransform(PxVec3(0.f,5.f,0.f),revoluteAngle), box2, PxTransform(PxVec3(0.f,-2.0f,0.f)));
			//RevoluteJoint* joint2 = new RevoluteJoint(nullptr, PxTransform(PxVec3(0.f, 5.f, 0.f),revoluteAngle), box, PxTransform(PxVec3(0.f, -3.1f, 0.f)));
			//box->Get()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			//box2->Get()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);*/

			////planets
			//Sphere* sun = new Sphere(PxTransform(PxVec3(0.0f, 10.0f, 0.0f)), 1.5f, 0.01f);
			//Sphere* planet1 = new Sphere(PxTransform(PxVec3(0.0f, 4.0f, 10.0f)),1.f,0.01f);
			//Sphere* planet2 = new Sphere(PxTransform(PxVec3(0.0f, 4.0f, 6.0f)),0.3f,0.01f);
			//Sphere* planet3 = new Sphere(PxTransform(PxVec3(0.0f, 4.0f, 3.0f)), 0.6f, 0.01f);
			//Sphere* moon = new Sphere(PxTransform(PxVec3(0.0f, 4.0f, 12.0f)), 0.2f, 0.01f);
			//Add(sun);
			//Add(planet1);
			////Add(planet2);
			////Add(planet3);
			//Add(moon);
			//sun->Get()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			//planet1->Get()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			//planet2->Get()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			//planet3->Get()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);


			//PxQuat revoluteAngle = PxQuat(PxPi / 2, PxVec3(0.f, 0.f, 1.f));
			//RevoluteJoint* orbit1 = new RevoluteJoint(nullptr, PxTransform(PxVec3(0.f, 11.f, 0.f),revoluteAngle), planet1, PxTransform(PxVec3(0.f, 0.f, 10.f)));
			//RevoluteJoint* orbit2 = new RevoluteJoint(nullptr, PxTransform(PxVec3(0.f, 11.f, 0.f),revoluteAngle), planet2, PxTransform(PxVec3(0.f, 0.f, 6.f)));
			//RevoluteJoint* orbit3 = new RevoluteJoint(nullptr, PxTransform(PxVec3(0.f, 11.f, 0.f),revoluteAngle), planet3, PxTransform(PxVec3(0.f, 0.f, 3.f)));
			//RevoluteJoint* moonOrbit = new RevoluteJoint(moon, PxTransform(PxVec3(0.f, 0.f, 2.f), revoluteAngle), planet1, PxTransform(PxVec3(0.f, 0.f, 0.f)));
			//orbit1->DriveVelocity(100*0.00274);
			//orbit1->SetLimits(0.2, 0.8);
			////orbit2->DriveVelocity(1.5);
			////orbit3->DriveVelocity(1.3);
			//moonOrbit->DriveVelocity(100*0.03571);
			//moonOrbit->SetLimits(0.2, 0.8);


			///*joint->DriveVelocity(0.5f);
			//joint2->DriveVelocity(3.f);*/

			//Triggers
			//box->SetTrigger(true, 0);
			box->SetKinematic(true, 0);

			sphere = new Sphere(PxTransform(-3.f, 0.5f, -19.f), 0.5f, 1.f);
			//Add(sphere);
			PxQuat revoluteAngle = PxQuat(PxPi / 2, PxVec3(1.f, 0.f, 0.f));


			HL_Domino* domino = new HL_Domino(PxTransform(PxVec3(5, 1, 0)));
			domino->Color(PxVec3(0, 0, 0));
			Add(domino);
			SphericalJoint* wheelTest = new SphericalJoint(domino, PxTransform(0.f, 0.f, 0.f, PxQuat(revoluteAngle)), sphere, PxTransform(PxVec3(0, 0, 1)));
			//wheelTest->DriveVelocity(1.2f);

			HL_DominoContainer* domcon = new HL_DominoContainer(PxVec3(-0, 0.5, 0), PxVec3(8, 0.5, 0));
			for (HL_Domino* dom : domcon->dominoesContained)
			{
				dom->Color(PxVec3(0, 0, 0));
				dom->Material(_materials->plasticMaterial);
				Add(dom);
			}

			HL_DominoContainer* domcon2 = new HL_DominoContainer(PxVec3(-0, 0.5, -0.5), PxVec3(-3, 0.5, -10));
			for (HL_Domino* dom : domcon2->dominoesContained)
			{
				dom->Color(PxVec3(0, 0, 0));
				dom->Material(_materials->plasticMaterial);
				Add(dom);
			}



			//Beginning of Domino Run. Shelf with dominoes running across, gradually getting larger-eventually moving a rubber ball.
			StaticBox* shelf = new StaticBox(PxTransform(-40, 40, 0), PxVec3(19, 0.5, 7));
			Add(shelf);

			HL_DominoContainer* domcon3 = new HL_DominoContainer(PxVec3(-58, 41, 0), PxVec3(-25, 41, 0));
			for (HL_Domino* dom : domcon3->dominoesContained)
			{
				dom->Color(PxVec3(0, 0, 0));
				dom->Material(_materials->plasticMaterial);
				Add(dom);
			}
			sphere = new Sphere(PxTransform(-24.f, 41.f, 0.f), 0.5f, 10.f);
			Add(sphere);
			sphere->Material(_materials->rubberMaterial,0);

			Sphere* sphere2 = new Sphere(PxTransform(-40.f, 43.f, 0.f), 0.8f, 1.f);
			Add(sphere2);

			//Remember to enable visualisation on joints
			Trampoline* _nTrampoline = new Trampoline(PxVec3(-18.f,0.f,0.f),PxVec3(2.f, 2.f, 2.f), 250.0f, 3.f);
			PxMaterial* trampMat = GetMaterial(HL_Materials::trampoline);
			_nTrampoline->top->GetShape()->setMaterials(&_materials->TrampolineMaterial,1);
			_nTrampoline->AddToScene(this);
			
/*
			for (int i = 0; i < 20; i++)
			{
				HL_DominoContainer* dominoRow = new HL_DominoContainer(PxVec3(20, 0.5, 12 + i), PxVec3(0, 0.5, 12 + i));
				for (HL_Domino* dom : dominoRow->dominoesContained)
				{
					dom->Color(PxVec3(0, 0, 0));
					Add(dom);
				}
			}
			Box* door = new Box(PxTransform(0, 4, 20), PxVec3(10, 0.03, 3.5), .5f);
			RevoluteJoint* doorJoint = new RevoluteJoint(nullptr, PxTransform(-1.5, 6.5, 20, PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.0f).getNormalized())), door, PxTransform(0, 0, 3));
			Add(door);


			HL_Stairs* stairs = new HL_Stairs(PxVec3(20, 20, 12), PxVec3(13, 0.5, 0));
			for (StaticBox* stair : stairs->_stairs)
			{
				Add(stair);
			}
			*/
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{

			for (HL_EventStruct* evt : hl_events->GetEvents())
			{

				if (evt->type == HL_EventType::ADDFORCE)
				{
					printf("ADDFORCE event detected\n");
					evt->rigBody->addForce(PxVec3(0, 15, 0), PxForceMode::eVELOCITY_CHANGE);

				}
			}
			hl_events->ClearEvents();


			//printf("update loop finished\n");
		}
		virtual void CustomInput(HL_PhysicsEngine::KeyState key_state[])
		{
			if (key_state['p'] == KeyState::DOWN)
			{
				printf("Projectile Launched\n");
				std::cout << camPos.x << " " << camDir.x << std::endl;
				HL_Projectile* proj = new HL_Projectile(camPos);
				Add(proj);
				proj->fireProjectile(camDir, 20.f);
			}
		}

		/// An example use of key release handling
		void ExampleKeyReleaseHandler()
		{
			cerr << "I am realeased!" << endl;
		}

		/// An example use of key presse handling
		void ExampleKeyPressHandler()
		{
			cerr << "I am pressed!" << endl;
		}
	};
}
