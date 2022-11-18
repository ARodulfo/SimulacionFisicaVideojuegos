#include "WhirlwindGenerator.h"

void WhirlwindGenerator::updateForce(Particle* particle, double t)
{
	//Masa infinita?
	if (fabs(particle->getInverseMass()) < 1e-10) return;

	//Drag force
	Vector3 whirlwindVel;
	whirlwindVel.z = whirlwindForce * (-(particle->getPos().x - whirlwindOrigin.x) - 0.2 * (particle->getPos().z - whirlwindOrigin.z));
	whirlwindVel.y = whirlwindForce * (20 -(particle->getPos().y - whirlwindOrigin.y));
	whirlwindVel.x = whirlwindForce * (particle->getPos().z - whirlwindOrigin.z) - 0.2 * (particle->getPos().x - whirlwindOrigin.x);

	Vector3 v = particle->getVel() - whirlwindVel;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;

	particle->addForce(dragF);
}