#pragma once
#include <map>
#include "RigidForceGenerator.h"
#include "SolidBodyInterface.h"

typedef std::pair<RigidForceGenerator*, SolidBody*> RFRPair;


class RigidBodyForceRegistry : public std::multimap<RigidForceGenerator*, SolidBody*>
{
public:
	void updateForces(double duration);

	void addRegistry(RigidForceGenerator* fg, SolidBody* p);

	void deleteBodyRegistry(SolidBody* p);
};

