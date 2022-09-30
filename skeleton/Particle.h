#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle();
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, int Mass);
	~Particle();

	void integrate(double t);

protected:
	Vector3 vel;
	physx::PxTransform pose;
	Vector3 acel;
	double damping;
	int mass;
	RenderItem* renderItem;
};