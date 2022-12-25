#pragma once
#include "RigidForceGenerator.h"
class SolidBodyExplosion : public RigidForceGenerator
{
public:
	SolidBodyExplosion(float radius, float blast, float time, Vector3 center) : 
		explosionRadius(radius), explosionBlast(blast), timeConstant(time), explosionCenter(center) {};
	virtual void updateForce(SolidBody* solidBody, float t);

	void setExplota() { explota = true; }
protected:
	float explosionRadius; //Radio de explosion
	float explosionBlast; //Fuerza de la explosi�n
	float timeConstant; //Constante de tiempo
	Vector3 explosionCenter; //Centro de la explosi�n
	bool explota = false;
};

