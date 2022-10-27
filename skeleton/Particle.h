#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	//Particle() { };
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass,float Gravity,RenderItem* ri, double tVida, bool viva, Vector3 aSpace);
	~Particle();

	void integrate(double t);
	void setVel(Vector3 velocidad);
	void setPos(Vector3 posicion);
	void setAcel(Vector3 aceleracion);
	void setDamp(double damp);
	void setMass(float masa);
	void setRender(RenderItem* proyectil);
	void setColor(Vector4 newColor);
	bool getViva();
	bool getInActionSpace();

	physx::PxTransform getPose();

	//virtual Particle* clone() const;

protected:
	Vector3 vel, acel;
	physx::PxTransform pose;
	double damping, _remaining_time;
	float mass;
	float gravity;
	RenderItem* renderItem;
	double tiempoVida;
	Vector3 actionSpace;

	bool estaViva;
};