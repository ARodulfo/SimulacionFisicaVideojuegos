#pragma once
#include "RigidForceGenerator.h"
class SolidBodyExplosion : public RigidForceGenerator
{
public:
	SolidBodyExplosion(float radius, float blast, float time, Vector3 center) : 
		explosionRadius(radius), explosionBlast(blast), timeConstant(time), explosionCenter(center) {};
	virtual void updateForce(SolidBody* solidBody, float t);
protected:
	float explosionRadius; //Radio de explosion
	float explosionBlast; //Fuerza de la explosión
	float timeConstant; //Constante de tiempo
	Vector3 explosionCenter; //Centro de la explosión
};

