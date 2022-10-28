#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, float Gravity, RenderItem* ri,double tVida, bool viva, Vector3 aSpace)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	vel = Vel;
	acel = Acel;
	gravity = Gravity;
	acel.y = gravity;

	damping = Damping;
	tiempoVida = tVida; 
	estaViva = viva;

	actionSpace = aSpace;

	renderItem = ri;
	renderItem->transform = &pose;
	renderItem->color = { 0.4,0.3,0.4,1 };
	

	//RegisterRenderItem(renderItem);
}

//bool Particula::checkSpace()
//{
//	if (position.p.x > actionSpace.x || position.p.y > actionSpace.y || position.p.z > actionSpace.z)return false;
//	else if (position.p.x < -actionSpace.x || position.p.y < -actionSpace.y || position.p.z < -actionSpace.z)return false;;
//	return true;
//
//}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{	
	pose.p = pose.p + vel * t;
	vel = vel * pow(damping, t) + acel * t;
	tiempoVida -= t;
	if (tiempoVida <= 0 || !getInActionSpace()) estaViva = false;
}

/*Particle* Particle::clone() const
{
	return nullptr;
}*/

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

void Particle::setColor(Vector4 newColor)
{
	renderItem->color = newColor;
}

void Particle::setTiempoVida(double tVida)
{
	tiempoVida = tVida;
}

bool Particle::getViva()
{
	return estaViva;
}

bool Particle::getInActionSpace()
{
	if (pose.p.x < -actionSpace.x || pose.p.y < -actionSpace.y || pose.p.z < -actionSpace.z) return false;
	else if (pose.p.x > actionSpace.x || pose.p.y > actionSpace.y || pose.p.z > actionSpace.z) return false;
	return true;
}



physx::PxTransform Particle::getPose()
{
	return pose;
}

Particle* Particle::clone(Vector3 pos, Vector3 vel, float grav, double tVida, Vector3 aSpace ) 
{
	return new Particle(pos, vel, { 0.0,0.0,0.0 }, 0.99, 100, grav, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), tVida, true, aSpace);;
}

