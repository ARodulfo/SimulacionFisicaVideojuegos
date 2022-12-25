#include "SolidBodySystem.h"

void SolidBodySystem::addBodies()
{
	if (colorR) {
		color = { (float(rand() % 10)) / 10.0f, (float(rand() % 10)) / 10.0f , (float(rand() % 10)) / 10.0f , 1 };
	}

	SolidBody* newBody = new SolidBody();
	newBody->rigid = physics->createRigidDynamic(systemPosition);
	PxShape* newShape = CreateShape(PxBoxGeometry(2, 2, 2), bodyMaterial);
	newBody->rigid->attachShape(*newShape);

	Vector3 vel = { -5.0f + rand() / (RAND_MAX / (10.0f)), -5.0f + rand() / (RAND_MAX / (10.0f)) , -5.0f + rand() / (RAND_MAX / (10.0f)) };
	newBody->rigid->setLinearVelocity(vel);
	int massRand = rand();
	while (massRand > 10 || massRand < 2)
	{
		massRand = rand();
	}
	newBody->rigid->setMass(massRand);

	if (inertia == 0)PxRigidBodyExt::updateMassAndInertia(*newBody->rigid, bodySize * bodySize * bodySize);
	else PxRigidBodyExt::updateMassAndInertia(*newBody->rigid, inertia);

	scene->addActor(*newBody->rigid);
	newBody->isnew = true;
	newBody->life = lifeTime;
	newBody->force = { 0.0, 0.0, 0.0 };
	newBody->torque = { 0.0, 0.0, 0.0 };
	newBody->item = new RenderItem(newShape, newBody->rigid, color);

	bodies.push_back(newBody);


	numBodies++;
	timeSinceAdded = 0;
}

void SolidBodySystem::update(float t)
{
	timeSinceAdded += t;

	if (timeSinceAdded > step && numBodies < maxBodies) {
		addBodies();
	}

	addForceRegistry(solidViento, getBodies());
	addExplosionForceRegistry(solidExplosion, getBodies());
	auto i = bodies.begin();

	forceRegistry.updateForces(t);

	while (i != bodies.end()) {
		(*i)->rigid->addForce((*i)->force, PxForceMode::eFORCE);
		(*i)->force = { 0.0, 0.0, 0.0 };
		(*i)->life -= t;

		if ((*i)->life < 0) {
			forceRegistry.deleteBodyRegistry((*i));
			delete((*i));
			i = bodies.erase(i);
		}
		else i++;
	}
}

void SolidBodySystem::setSizeInertia(float s, float i)
{
	bodySize = s;
	inertia = i;
}

std::vector<SolidBody*>& SolidBodySystem::getBodies()
{
	return bodies;
}
