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
#include "AnchoredSpringForceGenerator.h"
#include "SpringForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include "SolidBodySystem.h"
#include "SolidBodyInterface.h"

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
GaussianParticleGenerator* gaussianGen1 = NULL;
GaussianParticleGenerator* gaussianGen2 = NULL;
UniformParticleGenerator* uniformGen = NULL;

GravityForceGenerator* gravedad1 = NULL;
Vector3 gravedadInicial1{ 0,150,0 };
float variacionGravedad1 = 150;

GravityForceGenerator* gravedad2 = NULL;
Vector3 gravedadInicial2{ 0,30,0 };
float variacionGravedad2 = 30;

WindGenerator* viento = NULL;
float k1Wind = 0.7, k2Wind = 0.07;
Vector3 velocityWind{ 0,0,10 };

WhirlwindGenerator* torbellino = NULL;
float k1Whirlwind = 3, k2Whirlwind = 0.03, forceWhirlwind = 1;
Vector3 origenWhirlwind{ 0,0,0 };

ExplosionGenerator* explosion = NULL;
float radiusExplosion = 40, blastExplosion = 500000, tiempoExplosion = 2;
Vector3 centroExplosion{ 0,0,0 };

AnchoredSpringForceGenerator* muelleAncla = NULL;

SpringForceGenerator* gomaElastica1 = NULL;
SpringForceGenerator* gomaElastica2 = NULL;

Particle* agua = NULL;
physx::PxTransform* aguaPos = NULL;
BuoyancyForceGenerator* flotador = NULL;

physx::PxMaterial* defectMat = NULL;
SolidBodySystem* sistemaRigidos = NULL;


//vect <Proyectil> proyectiles;
ContactReportCallback gContactReportCallback;

int shootingMultiplier = 100;

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

	

	gravedad1 = new GravityForceGenerator({ 0,9.8,0 });

	muelleAncla = new AnchoredSpringForceGenerator(5.0, 10.0, { 0,70,-25 });
	
	Particle* particula1 = new Particle({ 0,50,-25 }, { 0,0,0 }, { 0,0,0 }, 0.99, 10, 9.8, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 200, true, { 1000.0,1000.0,1000.0 });


	
	sistema1 = new ParticleSystem();
	gaussianGen1 = new GaussianParticleGenerator({ 1,1,1 }, { 1,1,1 }, "fuente", { -45,50,0 }, { 0,-1,0 }, 1, 3, { 50.0,50.0,50.0 }, { 0,0,0 }, true);
	gaussianGen1->setType(HUMO);
	sistema1->addGenerator(gaussianGen1);
	gaussianGen2 = new GaussianParticleGenerator({ 1,1,1 }, { 0,0,0 }, "fuente", { 45,60,0 }, { 0,0,0 }, 1, 10, { 100.0,100.0,100.0 }, { 0,0,0 }, true);
	gaussianGen2->setType(LEAK);
	sistema1->addGenerator(gaussianGen2);

	viento = new WindGenerator(k1Wind, k2Wind, velocityWind);

	defectMat = gPhysics->createMaterial(0.2f, 0.2f, 0.5f);

	sistemaRigidos = new SolidBodySystem(gScene, gPhysics, { 0, 50, 0 }, defectMat);
	sistemaRigidos->setSizeInertia(6, 3);

	sistema1->addForceRegistry(gravedad1, particula1);
	sistema1->addForceRegistry(muelleAncla, particula1);
	sistema1->addParticle(particula1);


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
	// 
	// 
	// 
	// 
	// 
	sistemaRigidos->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	/*for (int i = 0; i < proyectiles.size(); i++) {
		delete proyectiles[i];
	}*/
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
		
		sistemaRigidos->shootRigid(GetCamera()->getDir()*shootingMultiplier, GetCamera()->getTransform());
		
		break;
	}
	case 'V':
	{

		/**/
		sistemaRigidos->setViento(Vector3(0, 0, 300));
		break;
	}
	case 'B':
	{
		sistemaRigidos->setViento(Vector3(0, 0, 0));
		break;
	}
	
	case 'E':
	{
		sistemaRigidos->addExplosionForceRegistry();
		break;
	}
	case '+':
	{
		shootingMultiplier += 10;
		std::cout << shootingMultiplier << "\n";
		break;
	}
	case '-':
	{
		shootingMultiplier -= 10;
		std::cout << shootingMultiplier << "\n";
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	//std::cout << "Se ha producido una colision\n";

	//sistemaRigidos->collisionFunc(actor1, actor2);

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