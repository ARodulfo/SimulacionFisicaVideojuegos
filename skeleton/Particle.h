#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	//Particle();
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass);
	~Particle();

	void integrate(double t);

protected:

	void setVel(Vector3 velocidad);
	void setPos(physx::PxTransform posicion);
	void setAcel(Vector3 aceleracion);
	void setDamp(double damp);
	void setMass(float masa);


	Vector3 vel;
	physx::PxTransform pose;
	Vector3 acel;
	double damping;
	float mass;
	RenderItem* renderItem;
};