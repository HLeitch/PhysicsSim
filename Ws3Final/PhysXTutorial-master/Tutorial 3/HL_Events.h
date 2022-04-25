#pragma once
//#include "BasicActors.h"
//#include "PhysicsEngine.h"
#include <vector>
#include <PxPhysicsAPI.h>

namespace HL_PhysicsEngine
{
	using namespace physx;

	enum HL_EventType
	{
		BASEEVENT = 0,
		DESTROYEVENT = 1,
		ADDFORCE = 2,
		TOUCHEVENT = 3,
	};

	struct HL_EventStruct
	{
		HL_EventType type = BASEEVENT;
		//Actor* actor1;
		//Actor* actor2;
		physx::PxActor* pxactor1;
		physx::PxActor* pxactor2;
		std::vector<PxReal> values;
		physx::PxRigidBody* rigBody;

		HL_EventStruct();
	};

	struct HL_ADDFORCEEVENT : HL_EventStruct
	{
		HL_ADDFORCEEVENT(PxRigidBody* actor);
	};

	//Singleton which provides an interface between classes using events.
	static class HL_Events
	{
	private:
		void SetInstance(HL_Events* _newInstance);
		HL_Events();

		std::vector<HL_EventStruct*> _events = std::vector<HL_EventStruct*>();

		HL_EventStruct* defaultEvent;

	protected:
		static HL_Events* _instance;


	public:
		static HL_Events* _GetInstance();

		std::vector<HL_EventStruct*> GetEvents();

		void ClearEvents();

		static void AddEvent(HL_EventStruct* _event)
		{
			_instance->_events.push_back(_event);
		}


	};
}
