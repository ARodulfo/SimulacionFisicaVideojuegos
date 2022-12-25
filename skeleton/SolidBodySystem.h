#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "SolidBodyInterface.h"
#include "RigidBodyForceRegistry.h"
#include "SolidBodyExplosion.h"
#include "SolidBodyWind.h"

class SolidBodySystem
{
private:
	std::vector<SolidBody*> bodies;
	RigidBodyForceRegistry forceRegistry;
	PxScene* scene;
	PxPhysics* physics;
	PxTransform systemPosition;
	float step;
	bool colorR;
	float lifeTime;
	float bodySize;
	float inertia = 0;
	int maxBodies;
	Vector4 color;
	physx::PxMaterial* bodyMaterial;
	float timeSinceAdded = 0;
	int numBodies;
	SolidBodyWind* solidViento;
	SolidBodyExplosion* solidExplosion;

	RenderItem* sueloI;

public:
	SolidBodySystem(PxScene* _scene, PxPhysics* _physics, PxTransform _sistPos, physx::PxMaterial* defMat = nullptr, float _step = 1, bool _colorR = true, float _life = 10, float _size = 1, int _max = 20, Vector4 _color = { 1,0,0,1 })
		: scene(_scene), physics(_physics), systemPosition(_sistPos), bodyMaterial(defMat), step(_step), colorR(_colorR), lifeTime(_life), bodySize(_size), maxBodies(_max), color(_color)
	{
		srand(time(NULL));

		PxShape* shape = CreateShape(PxBoxGeometry(100, 1, 100), nullptr);
		PxRigidStatic* ground = _physics->createRigidStatic({ 0,0,0 });

		ground->attachShape(*shape);
		scene->addActor(*ground);
		sueloI = new RenderItem(shape, ground, { 0.56, 0.5, 0.3, 1 });
		solidViento = new SolidBodyWind(Vector3(0, 0, 0));
		solidExplosion = new SolidBodyExplosion(200000, 100000, 100, { 0,0,0 });
	}

	~SolidBodySystem() {for (auto b : bodies) delete b;}

	void addBodies();
	void update(float t);
	void setSizeInertia(float s, float i);
	std::vector<SolidBody*>& getBodies();

	void explosionActiva() { 
		for (auto b : bodies) {
			b->bodyExplosionForce->setExplota();
		}
	}

	void addExplosionForceRegistry(SolidBodyExplosion* generator, const std::vector<SolidBody*>& bodies) {
		for (auto b : bodies) {
			forceRegistry.addRegistry(generator, b);
			b->bodyExplosionForce = generator;
		}
	};

	void addForceRegistry(RigidForceGenerator* generator, const std::vector<SolidBody*>& bodies) {
		for (auto b : bodies) {
			forceRegistry.addRegistry(generator, b);
		}
	};

	void setViento(const Vector3 windF) { solidViento->setWindForce(windF); }
};

