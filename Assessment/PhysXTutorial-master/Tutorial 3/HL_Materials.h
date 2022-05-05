#pragma once
#include "PhysicsEngine.h"
namespace HL_PhysicsEngine
{
	enum HL_Materials
	{
		basic = 0,
		carpet = 1,
		wood = 2,
		plastic = 3,
		ice = 4,
		rubber = 5,
		trampoline = 6,
	};



	class HL_MaterialsObject
	{
	public:
		HL_MaterialsObject();
		PxMaterial* TrampolineMaterial;
		PxMaterial* rubberMaterial;

		PxMaterial* basicMaterial;

		PxMaterial* carpetMaterial;

		PxMaterial* woodMaterial;

		PxMaterial* plasticMaterial;

		
		PxMaterial* iceMaterial;


	};
}
