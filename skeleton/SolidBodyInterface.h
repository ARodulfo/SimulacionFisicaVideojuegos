#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include <vector>
class BodyForceGenerator;
class SolidBodyExplosion;
using namespace physx;

struct SolidBody {
	PxRigidDynamic* rigid = nullptr;
	//PxRigidStatic* statRigid = nullptr;
	bool isnew;
	float life;
	RenderItem* item = nullptr;
	PxVec3 force;
	PxVec3 torque;

	~SolidBody() {
		DeregisterRenderItem(item);
		delete item;
	}

	/*std::vector<BodyForceGenerator*> bodyForcesRegistries;*/
	SolidBodyExplosion* bodyExplosionForce;
	PxRigidDynamic* getRigidDin() { return rigid; }
	//PxRigidStatic* getRigidStat() { return statRigid; }
};