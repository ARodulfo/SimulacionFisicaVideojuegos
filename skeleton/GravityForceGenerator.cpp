#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	//Check that the Particle has finite mass.
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	//Apply the mass scaled gravity;
	particle->addForce(-_gravity * particle->getMass());
}
