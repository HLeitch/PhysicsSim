#include "HL_Materials.h"


HL_PhysicsEngine::HL_MaterialsObject::HL_MaterialsObject()
{
	basicMaterial = CreateMaterial(0.3, 0.3, 0.3);

	carpetMaterial = CreateMaterial(0.6, 0.5, 0.1);
	//physlink.com coeffs; Model of the Relationship between the Velocity Restitution Coefficient and the Initial Car Velocity during Collision
	woodMaterial = CreateMaterial(0.25, 0.2, 0.5);
	//https://www.engineeringtoolbox.com/friction-coefficients-d_778.html
	plasticMaterial = CreateMaterial(0.45, 0.35, 0.2);

	//the coefficient of friction, particularly ice, allan mills 2008 https://iopscience.iop.org/article/10.1088/0031-9120/43/4/006
	iceMaterial = CreateMaterial(0.05,0.03,0.1);

	//http://isjos.org/JoP/vol4iss1/Papers/JoPv4i1-3Superball.pdf https://www.roymech.co.uk/Useful_Tables/Tribology/co_of_frict.htm
	rubberMaterial = CreateMaterial(1.16,0.8,0.86);
	TrampolineMaterial = CreateMaterial(1.2, 1.2, 0.92);
}
