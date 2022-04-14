#pragma once
#include "BasicActors.h"
#include "PhysicsEngine.h"

namespace HL_PhysicsEngine
{
	enum HL_EventType
	{
		BASEEVENT = 0,
		DESTROYEVENT = 1,
		ADDFORCE=2,



	};

	struct HL_EventStruct
	{
		HL_EventType type = BASEEVENT;
		Actor* actor1 = nullptr;
		Actor* actor2 = nullptr;
		PxActor* pxactor1 = nullptr;
		PxActor* pxactor2 = nullptr;
		vector<PxReal> values =  vector<PxReal>();
	};

	//Singleton which provides an interface between classes using events.
	static class HL_Events
	{
	private:
	    const HL_Events* _instance = nullptr;
		void SetInstance(HL_Events* _newInstance);

		vector<HL_EventStruct*> _events = vector<HL_EventStruct*>();

	public:
		static HL_Events* _GetInstance();

		vector<HL_EventStruct*> GetEvents();

		void ClearEvents();

		void AddEvent(HL_EventStruct* _event)
		{
			_events.push_back(_event);
		}


	};
}
