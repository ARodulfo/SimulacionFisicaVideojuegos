#include "WindGenerator.h"

void WindGenerator::updateForce(Particle* particle, double t)
{
	//Masa infinita?
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	//Drag force
	Vector3 v = particle->getVel() - windVelocity;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;

	particle->addForce(dragF);
}