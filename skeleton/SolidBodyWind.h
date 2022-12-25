#pragma once
#include "RigidForceGenerator.h"


class SolidBodyWind : public RigidForceGenerator
{
private: 
	Vector3 windForce;

public :
	SolidBodyWind(const Vector3 windF) : windForce(windF) {};
	void updateForce(SolidBody* body, float t);
};

