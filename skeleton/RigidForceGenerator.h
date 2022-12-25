#pragma once
#include "SolidBodyInterface.h"
#include <list>
#include <random>
#include <cmath>

class RigidForceGenerator
{
public:
	virtual void updateForce(SolidBody* solidBody, float t) = 0;
	std::string _name;
	double t = -1e10;
};

