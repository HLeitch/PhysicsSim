#include "HL_RectEnclosure.h"

HL_PhysicsEngine::HL_RectEnclosure::HL_RectEnclosure(PxTransform pose, PxVec3 dimensions, PxReal wallThickness, PxReal density) : DynamicActor(pose)
{
	this->CreateShape(PxBoxGeometry(dimensions.x, wallThickness, dimensions.z), density);
	GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f,-dimensions.y,0.f)));

	this->CreateShape(PxBoxGeometry(dimensions.x, dimensions.y, wallThickness), density);
	GetShape(1)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, dimensions.z)));

	this->CreateShape(PxBoxGeometry(dimensions.x, dimensions.y, wallThickness), density);
	GetShape(2)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, -dimensions.z)));

	this->CreateShape(PxBoxGeometry(wallThickness, dimensions.y, dimensions.z), density);
	GetShape(3)->setLocalPose(PxTransform(PxVec3(dimensions.x, 0.f,0.f)));

	this->CreateShape(PxBoxGeometry(wallThickness, dimensions.y, dimensions.z), density);
	GetShape(4)->setLocalPose(PxTransform(PxVec3(-dimensions.x, 0.f, 0.f)));
}
