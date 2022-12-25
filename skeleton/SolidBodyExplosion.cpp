#include "SolidBodyExplosion.h"

void SolidBodyExplosion::updateForce(SolidBody* solidBody, float t)
{
	if (!explota) return;
	//Force
	Vector3 force;
	float particleDistance = sqrt((pow(solidBody->rigid->getGlobalPose().p.x - explosionCenter.x, 2)) + (pow(solidBody->rigid->getGlobalPose().p.y - explosionCenter.y, 2)) + (pow(solidBody->rigid->getGlobalPose().p.z - explosionCenter.z, 2)));
	float coef = explosionBlast / (pow(particleDistance, 2));
	float expTime = exp(-(t / timeConstant));

	if (particleDistance < explosionRadius)
	{
		force = { coef * (solidBody->rigid->getGlobalPose().p.x - explosionCenter.x), coef * (solidBody->rigid->getGlobalPose().p.y - explosionCenter.y), coef * (solidBody->rigid->getGlobalPose().p.z - explosionCenter.z) };
		force *= expTime;
	}
	else
	{
		force = { 0,0,0 };
	}

	solidBody->rigid->addForce(force, PxForceMode::eACCELERATION);
	explota = false;
}
