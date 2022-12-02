#include "AnchoredSpringForceGenerator.h"

void AnchoredSpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 force = _other->getPos() - particle->getPos();

	const float length = force.normalize();
	const float delta_x = length - _resting_length;

	force *= delta_x * _k;

	particle->addForce(force);
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
{
	delete _other;
}
