#include "BuoyancyForceGenerator.h"
#include <iostream> 

void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	float h = particle->getPos().y;
	float h0 = _liquid_particle->getPos().y;

	Vector3 f(0, 0, 0);
	float inmersed = 0.0;
	if (h - h0 > _height * 0.5) {
		inmersed = 0.0;
		return;
	}
	else if(h0 - h > _height * 0.5) {
		inmersed = 1.0;
	}
	else {
		inmersed = (h0 - h) / _height + 0.5;
	}

	f.y = _liquid_density * _volume * inmersed ;

	particle->addForce(f);
}
