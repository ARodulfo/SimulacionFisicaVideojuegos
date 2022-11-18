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

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;
std::vector<Proyectil*>	proyectiles;
PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
Particle* gParticle = NULL;

ParticleSystem* sistema1 = NULL;
GaussianParticleGenerator* gaussianGen = NULL;
UniformParticleGenerator* uniformGen = NULL;

GravityForceGenerator* gravedad1 = NULL;
Vector3 gravedadInicial1{ 0,150,0 };
float variacionGravedad1 = 150;

GravityForceGenerator* gravedad2 = NULL;
Vector3 gravedadInicial2{ 0,30,0 };
float variacionGravedad2 = 30;

WindGenerator* viento = NULL;
float k1Wind = 0.7, k2Wind = 0.07;
Vector3 velocityWind{ 10,0,0 };

WhirlwindGenerator* torbellino = NULL;
float k1Whirlwind = 3, k2Whirlwind = 0.03, forceWhirlwind = 1;
Vector3 origenWhirlwind{ 0,0,0 };

ExplosionGenerator* explosion = NULL;
float radiusExplosion = 40, blastExplosion = 500000, tiempoExplosion = 2;
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
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

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
	gaussianGen = new GaussianParticleGenerator({ 10.5,10.5,10.5 }, { 0,0,0 }, "fuente", { 0,0,0 }, { 0,0,0 }, 20, 20, { 1000.0,1000.0,1000.0 }, {0,0,0}, true);
	//uniformGen = new UniformParticleGenerator({ 1.5,1.5,1.5 }, { 3.0,3.0,3.0 }, "fuente", { 1.0,1.0,1.0 }, { 10.0,25.0,2.0 }, 1, 2, 0.5, { 1000.0,1000.0,1000.0 });
	//sistema1->addGenerator(gaussianGen);
	//sistema1->createFireworkRules();
	//sistema1->generateFirework(sistema1->getFireworkRules()[2]);
	sistema1 = new ParticleSystem();

	gravedad1 = new GravityForceGenerator(gravedadInicial1);
	gravedad2 = new GravityForceGenerator(gravedadInicial2);

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

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case 'C':
	{
		//Proyectil* proy = new Proyectil(GetCamera()->getTransform().p, GetCamera()->getDir().getNormalized(), { 0.0,0.0,9.0 }, 0.99, 300, -50.00,CAÑON, new RenderItem(CreateShape(PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 6, true,{0,0,0});
		//Vector3 dir = GetCamera()->getDir().getNormalized();
		//proyectiles.push_back(proy);
		////new Proyectil(CAÑON);
		break;
	}
	case 'G':
	{
		variacionGravedad1 += 10;
		gravedad1->setGravity({ 0,variacionGravedad1,0 });
		Particle* particula1 = new Particle({ 0,15,0 }, { 0,50,0 }, { 0,0,0 }, 0.99, 0.2, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 20, true, { 1000.0,1000.0,1000.0 });
		particula1->setColor(Vector4{ 1,0,0,1 });
		sistema1->addForceRegistry(gravedad1, particula1);
		sistema1->addParticle(particula1);
		
		variacionGravedad2 += 10;
		gravedad1->setGravity({ 0,variacionGravedad2,0 });
		Particle* particula2 = new Particle({ 15,15,0 }, { 0,50,0 }, { 0,0,0 }, 0.99, 0.2, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 20, true, { 1000.0,1000.0,1000.0 });
		particula2->setColor(Vector4{ 0,1,0,1 });
		sistema1->addForceRegistry(gravedad2, particula2);
		sistema1->addParticle(particula2);
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

		/*Particle* particula1 = new Particle({ 15,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula2 = new Particle({ 0,0,15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula3 = new Particle({ 15,0,15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula4 = new Particle({ -15,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula5 = new Particle({ 0,0,-15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula6 = new Particle({ -15,0,-15 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula7 = new Particle({ 7,-5,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula8 = new Particle({ 0,-5,7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula9 = new Particle({ 7,-5,7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula10 = new Particle({ -7,-5,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula11 = new Particle({ 0,-5,-7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula12 = new Particle({ -7,-5,-7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula13 = new Particle({ 7,5,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula14 = new Particle({ 0,5,7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula15 = new Particle({ 7,5,7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula16 = new Particle({ -7,5,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula17 = new Particle({ 0,5,-7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula18 = new Particle({ -7,5,-7 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula19 = new Particle({ 0,-5,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });
		Particle* particula20 = new Particle({ 0,5,0 }, { 0,0,0 }, { 0,0,0 }, 0.99, 1, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 30, true, { 1000.0,1000.0,1000.0 });*/

		auto particleList = gaussianGen->generateParticles();
		
		blastExplosion += 500;
		radiusExplosion += 10;
		explosion->setBlast(blastExplosion);
		explosion->setRadius(radiusExplosion);

		for (auto particula : particleList) {
			sistema1->addParticleWithForce(explosion, particula);
		}

		/*sistema1->addForceRegistry(explosion, particula1);
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
		sistema1->addForceRegistry(explosion, particula7);
		sistema1->addParticle(particula7);
		sistema1->addForceRegistry(explosion, particula8);
		sistema1->addParticle(particula8);
		sistema1->addForceRegistry(explosion, particula9);
		sistema1->addParticle(particula9);
		sistema1->addForceRegistry(explosion, particula10);
		sistema1->addParticle(particula10);
		sistema1->addForceRegistry(explosion, particula11);
		sistema1->addParticle(particula11);
		sistema1->addForceRegistry(explosion, particula12);
		sistema1->addParticle(particula12);
		sistema1->addForceRegistry(explosion, particula13);
		sistema1->addParticle(particula13);
		sistema1->addForceRegistry(explosion, particula14);
		sistema1->addParticle(particula14);
		sistema1->addForceRegistry(explosion, particula15);
		sistema1->addParticle(particula15);
		sistema1->addForceRegistry(explosion, particula16);
		sistema1->addParticle(particula16);
		sistema1->addForceRegistry(explosion, particula17);
		sistema1->addParticle(particula17);
		sistema1->addForceRegistry(explosion, particula18);
		sistema1->addParticle(particula18);
		sistema1->addForceRegistry(explosion, particula19);
		sistema1->addParticle(particula19);
		sistema1->addForceRegistry(explosion, particula20);
		sistema1->addParticle(particula20);*/

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


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}