#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, RenderItem* ri)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	vel = Vel;
	acel = Acel;
	
	damping = Damping;

	renderItem = ri;
	renderItem->transform = &pose;
	renderItem->color = { 0.4,0.3,0.4,1 };
	

	//RegisterRenderItem(renderItem);
}


Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p + vel * t;
	vel = vel * pow(damping, t) + acel * t;
}

void Particle::setVel(Vector3 velocidad)
{
	vel = velocidad;
}

void Particle::setPos(Vector3 posicion)
{
	pose.p = posicion;
}

void Particle::setAcel(Vector3 aceleracion)
{
	acel = aceleracion;
}

void Particle::setDamp(double damp)
{
	damping = damp;
}

void Particle::setMass(float masa)
{
	mass = masa;
}

void Particle::setRender(RenderItem* proyectil)
{
	renderItem = proyectil;
}

physx::PxTransform Particle::getPose()
{
	return pose;
}

