#include "HL_StaticEnclosure.h"
#include <iostream>
namespace HL_PhysicsEngine
{
	std::vector<PxVec3>* HL_StaticEnclosure::SetVerts(PxReal width, PxReal height, PxReal depth, PxReal wallThck)
	{
		PxReal w = 0.5 * width;
		PxReal h = height;
		PxReal d = 0.5 * depth;
		PxReal t = wallThck;

		static PxVec3 ret[]{ PxVec3(-w,h,d),PxVec3(w,h,d), PxVec3(-w,0,d),PxVec3(w,0,d),PxVec3(-w,h,-d),PxVec3(-w,0,-d),PxVec3(w,h,-d),PxVec3(w,0,-d),PxVec3(0,0,0),PxVec3(0,0,0),PxVec3(-w + t,h,d - t),PxVec3(w - t,h, d - t),PxVec3(-w + t,t,d - t),PxVec3(w - t,t,d - t),PxVec3(w - t,h,-d + t),PxVec3(w - t,t,-d + t),PxVec3(-w + t,h,-d + t),PxVec3(-w + t,t,-d + t) };

		return new std::vector<PxVec3>(std::begin(ret), std::end(ret));
	}
	std::vector<PxVec3>* HL_StaticEnclosure::GetVerts(PxReal width, PxReal height, PxReal depth, PxReal wallThck)
	{
		if (this->_scaledVerts == nullptr)
		{
			this->_scaledVerts = SetVerts(width, height, depth, wallThck);
		}

		return this->_scaledVerts;
	}
	HL_StaticEnclosure::~HL_StaticEnclosure()
	{
		if (_scaledVerts != nullptr) {
			delete _scaledVerts;
		}
	}
	;

	HL_StaticEnclosure::HL_StaticEnclosure(PxReal width, PxReal height, PxReal depth, PxReal wallThck, const PxTransform& pose = PxTransform(PxIdentity)) :TriangleMesh((*GetVerts(width,height,depth,wallThck)), std::vector<PxU32>(std::begin(enclosureTris), std::end(enclosureTris)),pose)
	{

	};

	HL_DynamicEnclosure::HL_DynamicEnclosure(PxReal width, PxReal height, PxReal depth, PxReal wallThck, const PxTransform& pose,PxReal density) :ConvexMesh(*GetVerts(width,height,depth,wallThck),pose,density)
	{
	/*	PxQuat defaultRotation = pose.q* PxQuat(PxPi, PxVec3(0, 1, 0));
		PxTransform newTransform = PxTransform(pose.p, defaultRotation);
		this->GetShape()->setLocalPose(newTransform);*/
	}

	std::vector<PxVec3>* HL_DynamicEnclosure::SetVerts(PxReal width, PxReal height, PxReal depth, PxReal wallThck)
	{
		PxReal w = 0.5 * width;
		PxReal h = height;
		PxReal d = 0.5 * depth;
		PxReal t = wallThck;

		static PxVec3 ret[]{ PxVec3(-w,h,d),PxVec3(w,h,d), PxVec3(-w,0,d),PxVec3(w,0,d),PxVec3(-w,h,-d),PxVec3(-w,0,-d),PxVec3(w,h,-d),PxVec3(w,0,-d),PxVec3(0,0,0),PxVec3(0,0,0),PxVec3(-w + t,h,d - t),PxVec3(w - t,h, d - t),PxVec3(-w + t,t,d - t),PxVec3(w - t,t,d - t),PxVec3(w - t,h,-d + t),PxVec3(w - t,t,-d + t),PxVec3(-w + t,h,-d + t),PxVec3(-w + t,t,-d + t) };

		return new std::vector<PxVec3>(std::begin(ret), std::end(ret));
	}

	std::vector<PxVec3>* HL_DynamicEnclosure::GetVerts(PxReal width, PxReal height, PxReal depth, PxReal wallThck)
	{
		if (this->_scaledVerts == nullptr)
		{
			this->_scaledVerts = SetVerts(width, height, depth, wallThck);
		}

		return this->_scaledVerts;
	}

}