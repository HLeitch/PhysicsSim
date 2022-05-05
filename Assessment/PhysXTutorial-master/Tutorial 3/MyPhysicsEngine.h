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
	static const PxVec3 color_palette[] = { PxVec3(46.f / 255.f,9.f / 255.f,39.f / 255.f),PxVec3(217.f / 255.f,0.f / 255.f,0.f / 255.f),
		PxVec3(255.f / 255.f,45.f / 255.f,0.f / 255.f),PxVec3(255.f / 255.f,140.f / 255.f,54.f / 255.f),PxVec3(4.f / 255.f,117.f / 255.f,111.f / 255.f) };

	//pyramid vertices
	static PxVec3 pyramid_verts[] = { PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1) };
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = { 1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1 };

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose = PxTransform(PxIdentity), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose = PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts), end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs), end(pyramid_trigs)), pose)
		{
		}
	};

	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0 = (1 << 0),
			ACTOR1 = (1 << 1),
			ACTOR2 = (1 << 2)
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
		Trampoline(const PxVec3& dimensions = PxVec3(1.f, 1.f, 1.f), PxReal stiffness = 1.f, PxReal damping = 1.f)
		{
			PxReal thickness = .1f;
			bottom = new StaticBox(PxTransform(PxVec3(0.f, thickness, 0.f)), PxVec3(dimensions.x, thickness, dimensions.z));
			top = new Box(PxTransform(PxVec3(0.f, dimensions.y + thickness, 0.f)), PxVec3(dimensions.x, thickness, dimensions.z));
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, -dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, -dimensions.z)));


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
			top->GetShape()->setMaterials(&trampMat, 1);
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, -dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, -dimensions.z)));

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
		virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
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

		virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {}
		virtual void onWake(PxActor** actors, PxU32 count) {}
		virtual void onSleep(PxActor** actors, PxU32 count) {}
#if PX_PHYSICS_VERSION >= 0x304000
		virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {}
#endif
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
	{
		// let triggers through
		if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_CCD;


		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
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

		HL_MaterialsObject* _materials;

		DistanceJoint* string;

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
			this->_materials = new HL_MaterialsObject();
			px_scene->setFlag(PxSceneFlag::eENABLE_CCD,true);

			/*GetMaterial()->setDynamicFriction(.1f);
			GetMaterial()->setStaticFriction(0.5f);
			GetMaterial()->setRestitution(0.4f);*/

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);
			my_callback->_Gscene = this;

			plane = new Plane();
			plane->Color(PxVec3(160.f / 225.f, 196.f / 255.f, 226.f / 255.f));
			plane->Material(GetMaterial(HL_Materials::ice), 0);
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
			//Add(box);
			//Add(box2);
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
			//Add(domino);
			SphericalJoint* wheelTest = new SphericalJoint(domino, PxTransform(0.f, 0.f, 0.f, PxQuat(revoluteAngle)), sphere, PxTransform(PxVec3(0, 0, 1)));
			//wheelTest->DriveVelocity(1.2f);
			/*
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
			}*/

			Box* door = new Box(PxTransform(-32, 45.1, 0), PxVec3(0.15, 0.03, 0.15), 1.f);
			RevoluteJoint* doorJoint = new RevoluteJoint(nullptr, PxTransform(-32.2, 40.9f, 0, PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.0f).getNormalized())), door, PxTransform(0, 0, -.2f));

			//the string which is removed to start the domino run
			string = new DistanceJoint(nullptr, PxTransform(-32.3, 40.9f, 0), door, PxTransform(0, 0, 0));
			((PxDistanceJoint*)string->Get())->setMaxDistance(0.1);
			string->Stiffness(300.f);
			Add(door);
			door->Material(_materials->woodMaterial);
			door->Color(PxVec3(128.f / 255.f, 64.f / 255.f, 0.f / 255.f));



			//Beginning of Domino Run. Shelf with dominoes running across, gradually getting larger-eventually moving a rubber ball.
			StaticBox* shelf = new StaticBox(PxTransform(-22.5, 40, 0), PxVec3(10.5, 0.5, 7));
			Add(shelf);
			shelf->Material(_materials->woodMaterial);
			shelf->Color(PxVec3(123.f / 255.f, 109.f / 255.f, 93.f / 255.f));


			//startingDominoes are normal size increasing towards the end of the row. https://www.dominorules.com/introduction
			HL_DominoContainer* domcon3 = new HL_DominoContainer(PxVec3(-32, 40.096, 0), PxVec3(-25, 40.096, 0),PxVec3(0.023,0.046,0.01));
			for (HL_Domino* dom : domcon3->dominoesContained)
			{
				dom->Color(PxVec3(0, 0, 0));
				dom->Material(_materials->plasticMaterial);
				Add(dom);
			}
			//Dominoes increasing in size
			int increasingDoms = 60;
			PxVec3 position = PxVec3(-24.98, 40.f, 0);
			PxVec3 origSize = PxVec3(0.0075, 0.046, 0.023);
			for (int i = 0; i < increasingDoms; i++)
			{
				PxVec3 size =  origSize*((1+(0.09*i)));

				position += PxVec3(size.y*0.6+(size.z), 0.f,0.f);

				HL_Domino* largerDomino = new HL_Domino(PxTransform(position), size);
				largerDomino->Material(_materials->plasticMaterial);
				largerDomino->Color(PxVec3(0, 0, 0));
				Add(largerDomino);
			}

			sphere = new Sphere(PxTransform(-13.1f, 41.f, 0.f), 0.18f, 10.f);
			Add(sphere);
			sphere->Material(_materials->plasticMaterial, 0);
			sphere->Color(PxVec3(239.f / 255.f, 98.f / 255.f, 108.f / 255.f));
			((PxRigidBody*)sphere->Get())->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_CCD, true);

			//Remember to enable visualisation on joints
			Trampoline* _nTrampoline = new Trampoline(PxVec3(-10.5f, 0.f, 0.f), PxVec3(2.f, 2.f, 2.f), 25.0f, .5f);
			PxMaterial* trampMat = GetMaterial(HL_Materials::trampoline);
			_nTrampoline->top->GetShape()->setMaterials(&_materials->TrampolineMaterial, 1);
			_nTrampoline->AddToScene(this);

			HL_Image* img = new HL_Image(PxVec3(2.5, 0.04, 5.2), PxVec3(5, 0, 5));

			for (HL_DominoContainer* cont : img->DominoContainersHeld)
			{
				for (HL_Domino* dom : cont->dominoesContained)
				{
					dom->Material(_materials->plasticMaterial);
				}
			}
			img->AddToScene(this);


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
			//p for projectile
			if (key_state['p'] == KeyState::DOWN)
			{
				printf("Projectile Launched\n");
				std::cout << camPos.x << " " << camDir.x << std::endl;
				HL_Projectile* proj = new HL_Projectile(camPos);
				Add(proj);
				proj->fireProjectile(camDir, 20.f);
			}

			//b for begin
			if (key_state['b'] == KeyState::DOWN)
			{
				std::cout << "begining Dominio Run" << std::endl;
				//extend the maximum lenght of the string to allow the box to rotate, knocking over the first domino
				((PxDistanceJoint*)string->Get())->setMaxDistance(1.f);

				//Wake up the box to allow it to react to gravity
				PxRigidActor* act1, *act2;
				((PxDistanceJoint*)string->Get())->getActors(act1, act2);
				((PxRigidDynamic*)act2)->wakeUp();
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
