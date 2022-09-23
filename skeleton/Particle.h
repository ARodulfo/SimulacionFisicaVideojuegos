#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	physx::PxTransform pose;
	Vector3 acel;
	double damping;
	RenderItem* renderItem;
};