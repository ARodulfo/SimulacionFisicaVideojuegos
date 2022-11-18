#include "ExplosionGenerator.h"

void ExplosionGenerator::updateForce(Particle* particle, double t)
{
	//Masa infinita?
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	//Force

	float particleDistance = sqrt((pow(particle->getPos().x - explosionCenter.x, 2)) + (pow(particle->getPos().y - explosionCenter.y, 2)) + (pow(particle->getPos().z - explosionCenter.z, 2)));
	float coef = explosionBlast / (pow(particleDistance, 2));
	float expTime = exp(-(t / timeConstant));

	if (particleDistance < explosionRadius)
	{
		Vector3 force{ coef * (particle->getPos().x - explosionCenter.x), coef * (particle->getPos().y - explosionCenter.y), coef * (particle->getPos().z - explosionCenter.z) };
		force *= expTime;
		particle->addForce(force);
	}
	else
	{
		Vector3 force{ 0,0,0 };
		particle->addForce(force);
	}
}