#include "RigidBodyForceRegistry.h"

void RigidBodyForceRegistry::updateForces(double duration) {
	for (auto it = this->begin(); it != this->end(); it++) {
		it->first->updateForce(it->second, duration);
	}
}

void RigidBodyForceRegistry::addRegistry(RigidForceGenerator* fg, SolidBody* p) {
	insert(RFRPair{ fg,p });
}

void RigidBodyForceRegistry::deleteBodyRegistry(SolidBody* p) {
	for (auto it = begin(); it != end();) {
		if (it->second == p) it = erase(it);
		else it++;
	}
}
