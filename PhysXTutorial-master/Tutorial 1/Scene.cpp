#include "Scene.h"
#include "PhysicsEngine.h"
namespace PhysicsEngine
{
	///Scene methods
	void Scene::Init()
	{
		//scene
		PxSceneDesc sceneDesc(GetPhysics()->getTolerancesScale());

		if (!sceneDesc.cpuDispatcher)
		{
			PxDefaultCpuDispatcher* mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
			sceneDesc.cpuDispatcher = mCpuDispatcher;
		}

		if (!sceneDesc.filterShader)
			sceneDesc.filterShader = PxDefaultSimulationFilterShader;

		px_scene = GetPhysics()->createScene(sceneDesc);

		if (!px_scene)
			throw new Exception("PhysicsEngine::Scene::Init, Could not initialise the scene.");

		//default gravity
		px_scene->setGravity(PxVec3(0.0f, -9.81f, 0.0f));

		CustomInit();
	}

	void Scene::Update(PxReal dt)
	{
		CustomUpdate();

		px_scene->simulate(dt);
		px_scene->fetchResults(true);
	}

	void Scene::Add(Actor* actor)
	{
		px_scene->addActor(*actor->Get());
	}

	PxScene* Scene::Get()
	{
		return px_scene;
	}

	void Scene::Reset()
	{
		px_scene->release();
		Init();
	}
}