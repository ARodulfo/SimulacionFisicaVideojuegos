#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Proyectil.h"
#include "ParticleSystem.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GravityForceGenerator.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"
#include "ExplosionGenerator.h"

#include <iostream>
#include <vector>



using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;
std::vector<Proyectil*>	proyectiles;
PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
Particle* gParticle = NULL;

ParticleSystem* sistema1 = NULL;
GaussianParticleGenerator* gaussianGen = NULL;
UniformParticleGenerator* uniformGen = NULL;

GravityForceGenerator* gravedad = NULL;
Vector3 gravedadInicial{ 0,150,0 };
float variacionGravedad = 150;

WindGenerator* viento = NULL;
float k1Wind = 0.7, k2Wind = 0.07;
Vector3 velocityWind{ 10,0,0 };

WhirlwindGenerator* torbellino = NULL;
float k1Whirlwind = 3, k2Whirlwind = 0.03, forceWhirlwind = 1;
Vector3 origenWhirlwind{ 0,0,0 };

ExplosionGenerator* explosion = NULL;
float radiusExplosion = 30, blastExplosion = 25, tiempoExplosion = 2;
Vector3 centroExplosion{ 0,0,0 };



//vect <Proyectil> proyectiles;
ContactReportCallback gContactReportCallback;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	/*Vector3 Pos = { 0.0, 0.0, 0.0 };
	Vector3 Vel = { 0.0, 0.0, 0.0 };
	Vector3 Acel = { 0.0,0.0,0.0 };
	double Damping = 0.999;
	int Mass = 0;
	float Gravity = 0;
	gParticle = new Particle(GetCamera()->getTransform().p +  Vector3{ -100,0,-100 }, Vel, Acel, Damping, Mass, Gravity,new RenderItem(CreateShape(PxSphereGeometry(2.25)), Vector4(1, 0, 1, 1)),6, true);*/

	//sistema1 = new ParticleSystem();
	//gaussianGen = new GaussianParticleGenerator({ 1.5,1.5,1.5 }, { 3.0,3.0,3.0 }, "fuente", { 1.0,1.0,1.0 }, { 10.0,25.0,2.0 }, 1, 5, { 1000.0,1000.0,1000.0 }, {0,0,0}, true);
	//uniformGen = new UniformParticleGenerator({ 1.5,1.5,1.5 }, { 3.0,3.0,3.0 }, "fuente", { 1.0,1.0,1.0 }, { 10.0,25.0,2.0 }, 1, 2, 0.5, { 1000.0,1000.0,1000.0 });
	//sistema1->addGenerator(gaussianGen);
	//sistema1->createFireworkRules();
	//sistema1->generateFirework(sistema1->getFireworkRules()[2]);
	sistema1 = new ParticleSystem();

	gravedad = new GravityForceGenerator(gravedadInicial);

	viento = new WindGenerator(k1Wind, k2Wind, velocityWind);

	torbellino = new WhirlwindGenerator(k1Whirlwind, k2Whirlwind, origenWhirlwind, forceWhirlwind);

	explosion = new ExplosionGenerator(radiusExplosion, blastExplosion, tiempoExplosion, centroExplosion);

	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	/*for (int i = 0; i < proyectiles.size(); i++) {
		proyectiles[i]->integrate(t);
	}*/
	gScene->simulate(t);
	gScene->fetchResults(true);
	/*gParticle->integrate(t);*/
	sistema1->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	for (int i = 0; i < proyectiles.size(); i++) {
		delete proyectiles[i];
	}
	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	/*gParticle->~Particle();*/
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'C':
	{
		//Proyectil* proy = new Proyectil(GetCamera()->getTransform().p, GetCamera()->getDir().getNormalized(), { 0.0,0.0,9.0 }, 0.99, 300, -50.00,CA�ON, new RenderItem(CreateShape(PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 6, true,{0,0,0});
		//Vector3 dir = GetCamera()->getDir().getNormalized();
		//proyectiles.push_back(proy);
		////new Proyectil(CA�ON);
		break;
	}
	case 'G':	
	{
		variacionGravedad += 10;
		gravedad->setGravity({ 0,variacionGravedad,0 });
		Particle* particula = new Particle({ 0,15,0 }, { 0,150,0 }, { 0,0,0 }, 0.99, 0.2, 9.8,new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 3, true, { 1000.0,1000.0,1000.0 });
		sistema1->addForceRegistry(gravedad, particula);
		sistema1->addParticle(particula);
		break;
	}
	case 'V':
	{
		k1Wind -= 0.1;
		k2Wind -= 0.01;
		viento->setDrag(k1Wind, k2Wind);
		Particle* particula = new Particle({ 0,0,0 }, { -140,0,0 }, { 0,0,0 }, 0.99, 0.2, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 20, true, { 1000.0,1000.0,1000.0 });
		sistema1->addForceRegistry(viento, particula);
		sistema1->addParticle(particula);
		break;
	}
	case 'T':
	{
		forceWhirlwind += 0.02;
		torbellino->setForce(forceWhirlwind);
		Particle* particula = new Particle({ 0,15,0 }, { 15,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		sistema1->addForceRegistry(torbellino, particula);
		sistema1->addParticle(particula);
		break;
	}
	case 'E':
	{
		Particle* particula1 = new Particle({ 15,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula2 = new Particle({ 0,0,15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula3 = new Particle({ 15,0,15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula4 = new Particle({ -15,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula5 = new Particle({ 0,0,-15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula6 = new Particle({ -15,0,-15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });

		blastExplosion += 50;
		radiusExplosion += 5;
		explosion->setBlast(blastExplosion);
		explosion->setRadius(radiusExplosion);

		sistema1->addForceRegistry(explosion, particula1);
		sistema1->addParticle(particula1);
		sistema1->addForceRegistry(explosion, particula2);
		sistema1->addParticle(particula2);
		sistema1->addForceRegistry(explosion, particula3);
		sistema1->addParticle(particula3);
		sistema1->addForceRegistry(explosion, particula4);
		sistema1->addParticle(particula4);
		sistema1->addForceRegistry(explosion, particula5);
		sistema1->addParticle(particula5);
		sistema1->addForceRegistry(explosion, particula6);
		sistema1->addParticle(particula6);

		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}