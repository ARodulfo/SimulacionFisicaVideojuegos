#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, int Mass)
{
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	vel = Vel;
	acel = Acel;
	damping = Damping;


	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pose, { 1.0,1.0,1.0,1.0 });

	//RegisterRenderItem(renderItem);
}

Particle::Particle() {

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
