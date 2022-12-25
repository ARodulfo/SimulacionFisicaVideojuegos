#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include "SolidBodyInterface.h"
#include "ParticleForceRegistry.h"
class SolidBodySystem
{
public:
	SolidBodySystem(PxScene* _scene, PxPhysics* _physics, ParticleForceRegistry* _forceRegistry, PxTransform _p, physx::PxMaterial* mat = nullptr, float _step = 1.5, bool _colorR = true, float _life = 10, float _size = 3, int _max = 20, Vector4 _color = { 1,0,0,1 });


private:
	std::vector<SolidBody*> bodies;
	ParticleForceRegistry* forceRegistry;
	PxScene* scene;
	PxPhysics* physics;
	PxTransform p;
	float step;
	bool colorR;
	float life;
	float size;
	float inertia = 0;
	int max;
	Vector4 color;
	physx::PxMaterial* m;

	float timeSinceAdded;
	int numBodies;
};

