#include "HL_Events.h"

namespace HL_PhysicsEngine
{
	void HL_Events::SetInstance(HL_Events* _newInstance)
	{
		_instance = _newInstance;
	}

	HL_Events* HL_Events::_GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new HL_Events();
		}




		return _instance;
	}

	vector<HL_Events*> HL_PhysicsEngine::HL_Events::GetEvents()
	{
		return _events;
	}

	void HL_PhysicsEngine::HL_Events::ClearEvents()
	{


	}
}