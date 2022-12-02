#include "SpringForceGenerator.h"

void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 f = particle->getPos();
	f -= _other->getPos();

	float length = f.normalize();
	length = (length - _resting_length);
	if (length <= 0.0f) return;

	f *= -(length * _k);
	particle->addForce(f);
}
