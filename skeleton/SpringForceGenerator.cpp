#include "SpringForceGenerator.h"

void SpringForceGenerator::updateForce(Particle* particle)
{
	Vector3 force = _other->getPos() - particle->getPos();

	const float length = force.normalize();
	const float delta_x = length - _resting_length;

	force *= delta_x * _k;

	particle->addForce(force);
}
