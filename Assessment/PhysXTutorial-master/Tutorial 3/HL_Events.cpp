#include "HL_Events.h"
#include <PxPhysicsAPI.h>
#include <vector>
#include <iostream>
namespace HL_PhysicsEngine
{
	HL_Events* HL_Events::_instance = nullptr;


	HL_Events::HL_Events()
	{
		_events = std::vector<HL_EventStruct*>();
		defaultEvent = new HL_EventStruct();
		defaultEvent->type = HL_EventType::BASEEVENT;
		_events.push_back(defaultEvent);
	}

	void HL_Events::SetInstance(HL_Events* _newInstance)
	{
		_instance = _newInstance;
	}

	HL_Events* HL_PhysicsEngine::HL_Events::_GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new HL_Events();
		}

		return _instance;
	}

	std::vector<HL_EventStruct*> HL_PhysicsEngine::HL_Events::GetEvents()
	{
		return  this->_events;
	}


	void HL_PhysicsEngine::HL_Events::ClearEvents()
	{
		_events.erase(_events.begin() + 1, _events.end());
		
		_events.shrink_to_fit();
		
		//_events.push_back(defaultEvent);
	}
	HL_EventStruct::HL_EventStruct()
	{
		values = std::vector<PxReal>();
	}
	HL_ADDFORCEEVENT::HL_ADDFORCEEVENT(PxRigidBody* actor):HL_EventStruct()
	{
		this->type = HL_EventType::ADDFORCE;
		this->rigBody = actor;

	}
	HL_STARTINGEVENT::HL_STARTINGEVENT():HL_EventStruct()
	{
		this->type = HL_EventType::STARTINGEVENT;
	}
}