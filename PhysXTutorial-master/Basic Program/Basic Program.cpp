#include <iostream> //cout, cerr
#include <iomanip> //stream formatting
#include <windows.h> //delay function
#include <PxPhysicsAPI.h> //PhysX

using namespace std;
using namespace physx;

//PhysX objects
PxPhysics* physics = 0;
PxFoundation* foundation = 0;
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
debugger::comm::PvdConnection* pvd = 0;
#else
PxPvd*  pvd = 0;
#endif

//simulation objects
PxScene* scene;

//Floor Boxes
PxRigidStatic* staticFloorBox;
PxRigidDynamic* dynamicFloorBox;
PxRigidDynamic* kinematicFloorBox;

//Sky Boxes 
PxRigidDynamic* skyBox1;
PxRigidDynamic* skyBox2;
PxRigidDynamic* skyBox3;

PxRigidDynamic* box;
PxRigidStatic* plane;
PxMaterial* default_material;

//Workshop 1: variables
int g_frameNumber {};

///Initialise PhysX objects
bool PxInit()
{
	//default error and allocator callbacks
	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;

	//Init PhysX
	//foundation
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
#else
	foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
#endif

	if(!foundation)
		return false;

	//connect to an external visual debugger (if exists)
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
	pvd = PxVisualDebuggerExt::createConnection(physics->getPvdConnectionManager(), "localhost", 5425, 100,
		PxVisualDebuggerExt::getAllConnectionFlags());
#else
	pvd = PxCreatePvd(*foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
	pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
#endif

	//physics
#if PX_PHYSICS_VERSION < 0x304000 // SDK 3.3
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale());
#else
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);
#endif

	if(!physics)
		return false;

	//create a default scene
	PxSceneDesc sceneDesc(physics->getTolerancesScale());

	if(!sceneDesc.cpuDispatcher)
	{
		PxDefaultCpuDispatcher* mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
		sceneDesc.cpuDispatcher = mCpuDispatcher;
	}

	if(!sceneDesc.filterShader)
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	scene = physics->createScene(sceneDesc);

	if (!scene)
		return false;

	return true;
}

/// Release all allocated resources
void PxRelease()
{
	if (scene)
		scene->release();
	if (physics)
		physics->release();
	if (pvd)
		pvd->release();
	if (foundation)
		foundation->release();
}
PxRigidDynamic* CreateBox(PxVec3 initalPosition, PxVec3 dimensions, PxReal density)
{
	PxRigidDynamic* newBox = physics->createRigidDynamic(PxTransform(initalPosition));
	newBox->createShape(PxBoxGeometry(dimensions), *default_material);

	PxRigidBodyExt::updateMassAndInertia(*newBox, 1.f); //density of 1kg/m^3

	scene->addActor(*newBox);
	return(newBox);
}

PxRigidDynamic* CreateSphere(PxVec3 initalPosition, PxReal dimension, PxReal density)
{
	PxRigidDynamic* newBox = physics->createRigidDynamic(PxTransform(initalPosition));
	newBox->createShape(PxSphereGeometry(dimension), *default_material);

	PxRigidBodyExt::updateMassAndInertia(*newBox, 1.f); //density of 1kg/m^3

	scene->addActor(*newBox);
	return(newBox);
}

PxRigidDynamic* CreateCapsule(PxVec3 initalPosition, PxReal dimension, PxReal density)
{
	PxRigidDynamic* newBox = physics->createRigidDynamic(PxTransform(initalPosition));
	newBox->createShape(PxCapsuleGeometry(dimension,dimension/2), *default_material);

	PxRigidBodyExt::updateMassAndInertia(*newBox, 1.f); //density of 1kg/m^3

	scene->addActor(*newBox);
	return(newBox);
}

///Initialise the scene
void InitScene()
{
	//default gravity
	scene->setGravity(PxVec3(0.f, -9.81f, 0.f));

	//materials
	 default_material = physics->createMaterial(0.f, .6f, .6f);   //static friction, dynamic friction, restitution

	//create a static plane (XZ)
	plane = PxCreatePlane(*physics, PxPlane(PxVec3(0.f, 1.f, 0.f), 0.f), *default_material);
	scene->addActor(*plane);

	//Dynamic Floor Box
	//create a dynamic actor and place it 10 m above the ground
	box = physics->createRigidDynamic(PxTransform(PxVec3(3.f, .5f, 0.f)));
	//create a box shape of 1m x 1m x 1m size (values are provided in halves)
	box->createShape(PxBoxGeometry(.5f, .5f, .5f), *default_material);
	//update the mass of the box
	PxRigidBodyExt::updateMassAndInertia(*box, 1.f); //density of 1kg/m^3


	//Static Floor Box
	staticFloorBox = physics->createRigidStatic(PxTransform(PxVec3(0.f, 0.5f, 0.f)));
	staticFloorBox->createShape(PxBoxGeometry(.5f, .5f, .5f), *default_material);



	//Kinematic Floor Box
	kinematicFloorBox = physics->createRigidDynamic(PxTransform(PxVec3(-3.f, .5f, 0.f)));
	kinematicFloorBox->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	kinematicFloorBox->createShape(PxBoxGeometry(.5f, .5f, .5f), *default_material);

	//Boxes appearing from the skyyy

	skyBox1 = physics->createRigidDynamic(PxTransform(PxVec3(3.f, 50.f, 0.f)));
	skyBox1->createShape(PxBoxGeometry(.5f, .5f, .5f), *default_material);

	skyBox2 = physics->createRigidDynamic(PxTransform(PxVec3(0.f, 50.f, 0.f)));
	skyBox2->createShape(PxBoxGeometry(.5f, .5f, .5f), *default_material);

	skyBox3 = physics->createRigidDynamic(PxTransform(PxVec3(-3.f, 50.f, 0.f)));
	skyBox3->createShape(PxBoxGeometry(.5f, .5f, .5f), *default_material);

	scene->addActor(*box);
	scene->addActor(*staticFloorBox);
	scene->addActor(*kinematicFloorBox);
	
	for (int i = 0; i < 10; i++)
	{
		CreateBox(PxVec3((i * 2.07f), 50.f, 2.f), PxVec3(.5f, .9f, .5f), PxReal(2));
	}
	
	for (int i = 0; i < 10; i++)
	{
		CreateSphere(PxVec3((i * 2.07f), 50.f, 0.f), PxReal(0.7), PxReal(2));
	}

	for (int i = 0; i < 10; i++)
	{
		CreateCapsule(PxVec3((i * 2.57f), 50.f, -2.f), PxReal(0.75), PxReal(2));
	}


	//workshop 1:
	g_frameNumber = 0;
}



/// Perform a single simulation step
void Update(PxReal delta_time)
{
	scene->simulate(delta_time);
	scene->fetchResults(true);
}

void moveBox()
{
	PxTransform newPose = box->getGlobalPose();

	PxVec3 pos = newPose.p + PxVec3(10.f, 0.f, 0.f);
	newPose.p = pos;
	box->setGlobalPose(newPose);
}

void stopBox()
{

	box->setLinearVelocity(PxVec3(0, 0, 0));


}
/// The main function
int main()
{
	//initialise PhysX	
	if (!PxInit())
	{
		cerr << "Could not initialise PhysX." << endl;
		return 0;
	}

	//initialise the scene
	InitScene();

	//set the simulation step to 1/60th of a second
	PxReal delta_time = 1.f/60.f;

	cout << "box mass = " << box->getMass() << endl;

	PxVec3 forceVector = PxVec3(200, 500, 0);
	//box->addForce(forceVector);
	//simulate until the 'Esc' is pressed
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		g_frameNumber++;
		//'visualise' position and velocity of the box
		PxVec3 position = box->getGlobalPose().p;
		PxVec3 velocity = box->getLinearVelocity();

		//Workshop 1
		cout << "Frame: " << g_frameNumber << "-->";

		if (position.x > 10)
		{
			stopBox();
		}
		//

		cout << setiosflags(ios::fixed) << setprecision(2) << "x=" << position.x << 
			", y=" << position.y << ", z=" << position.z << ",  ";
		cout << setiosflags(ios::fixed) << setprecision(2) << "vx=" << velocity.x << 
			", vy=" << velocity.y << ", vz=" << velocity.z << endl;

		//perform a single simulation step
		Update(delta_time);
		
		//introduce 100ms delay for easier visual analysis of the results
		Sleep(10);
	}

	//Release all resources
	PxRelease();

	return 0;
}


