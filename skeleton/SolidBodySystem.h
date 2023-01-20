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
	std::vector<SolidBody*> balls;
	std::vector<PxRigidStatic*> statBodies;
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
	float timeSinceAdded = 4;
	int numBodies;
	SolidBodyWind* solidViento;
	SolidBodyExplosion* solidExplosion;
	bool pointBlock = false;

	RenderItem* suelo;
	RenderItem* techo;
	RenderItem* paredDelante1;
	RenderItem* paredDelante2;
	RenderItem* paredDelante3;
	RenderItem* paredDetras;
	RenderItem* paredDerecha;
	RenderItem* paredIzquierda;

	PxRigidStatic* columna1;
	PxRigidStatic* columna2;
	PxRigidStatic* columna3;
	PxRigidStatic* columna4;
	PxRigidStatic* columna5;

public:
	SolidBodySystem(PxScene* _scene, PxPhysics* _physics, PxTransform _sistPos, physx::PxMaterial* defMat = nullptr, float _step = 1, bool _colorR = true, float _life = 10, float _size = 1, int _max = 20, Vector4 _color = { 1,0,0,1 })
		: scene(_scene), physics(_physics), systemPosition(_sistPos), bodyMaterial(defMat), step(_step), colorR(_colorR), lifeTime(_life), bodySize(_size), maxBodies(_max), color(_color)
	{
		srand(time(NULL));

		float xPos;
		float zPos;

		PxShape* shape = CreateShape(PxBoxGeometry(100, 1, 100), nullptr); //Abajo
		PxRigidStatic* ground = _physics->createRigidStatic({ 0,0,0 });
		ground->attachShape(*shape);
		scene->addActor(*ground);
		suelo = new RenderItem(shape, ground, { 0.56, 0.5, 0.3, 1 });
		

		PxShape* shape2 = CreateShape(PxBoxGeometry(1, 100, 100), nullptr); //Izquierda
		PxRigidStatic* leftWall = _physics->createRigidStatic({ -100,0,0 });
		leftWall->attachShape(*shape2);
		scene->addActor(*leftWall);
		paredIzquierda = new RenderItem(shape2, leftWall, { 0.56, 0.5, 0.3, 1 });
		
		PxShape* shape3 = CreateShape(PxBoxGeometry(1, 100, 100), nullptr); //Derecha
		PxRigidStatic* rightWall = _physics->createRigidStatic({ 100,0,0 });
		rightWall->attachShape(*shape3);
		scene->addActor(*rightWall);
		paredDerecha = new RenderItem(shape3, rightWall, { 0.56, 0.5, 0.3, 1 });

		PxShape* shape4 = CreateShape(PxBoxGeometry(100, 1, 100), nullptr); //Arriba
		PxRigidStatic* roof = _physics->createRigidStatic({ 0,100,0 });
		roof->attachShape(*shape4);
		scene->addActor(*roof);
		techo = new RenderItem(shape4, roof, { 0.56, 0.5, 0.3, 1 });

		PxShape* shape5 = CreateShape(PxBoxGeometry(100, 100, 1), nullptr); //Detrás
		PxRigidStatic* backWall = _physics->createRigidStatic({ 0,50,100 });
		backWall->attachShape(*shape5);
		scene->addActor(*backWall);
		paredDetras = new RenderItem(shape5, backWall, { 0.56, 0.5, 0.3, 1 });

		PxShape* shape6 = CreateShape(PxBoxGeometry(50, 100, 1), nullptr); //Delante
		PxRigidStatic* frontWall1 = _physics->createRigidStatic({ -60,50,-100 });
		frontWall1->attachShape(*shape6);
		scene->addActor(*frontWall1);
		paredDelante1 = new RenderItem(shape6, frontWall1, { 0.56, 0.5, 0.3, 1 });

		PxShape* shape7 = CreateShape(PxBoxGeometry(20, 100, 1), nullptr); //Delante
		PxRigidStatic* frontWall2 = _physics->createRigidStatic({ 0,110,-100 });
		frontWall2->attachShape(*shape7);
		scene->addActor(*frontWall2);
		paredDelante2 = new RenderItem(shape7, frontWall2, { 0.56, 0.5, 0.3, 1 });

		PxShape* shape8 = CreateShape(PxBoxGeometry(50, 100, 1), nullptr); //Delante
		PxRigidStatic* frontWall3 = _physics->createRigidStatic({ 60,50,-100 });
		frontWall3->attachShape(*shape8);
		scene->addActor(*frontWall3);
		paredDelante3 = new RenderItem(shape8, frontWall3, { 0.56, 0.5, 0.3, 1 });

		xPos = rand() % 180 - 90;
		//float yPos = rand() % 81 + 10;
		zPos = rand() % 101 - 50;
		PxShape* newShape= CreateShape(PxBoxGeometry(5, 8, 5), nullptr);
		columna1 = physics->createRigidStatic({ xPos, 9, zPos });
		columna1->attachShape(*newShape);
		scene->addActor(*columna1);
		RenderItem*  renderNewBlock = new RenderItem(newShape, columna1, color);

		xPos = rand() % 180 - 90;
		//float yPos = rand() % 81 + 10;
		zPos = rand() % 101 - 50;
		newShape = CreateShape(PxBoxGeometry(5, 8, 5), nullptr);
		columna2 = physics->createRigidStatic({ xPos, 9, zPos });
		columna2->attachShape(*newShape);
		scene->addActor(*columna2);
		renderNewBlock = new RenderItem(newShape, columna2, color);

		xPos = rand() % 180 - 90;
		//float yPos = rand() % 81 + 10;
		zPos = rand() % 101 - 50;
		newShape = CreateShape(PxBoxGeometry(5, 8, 5), nullptr);
		columna3 = physics->createRigidStatic({ xPos, 9, zPos });
		columna3->attachShape(*newShape);
		scene->addActor(*columna3);
		renderNewBlock = new RenderItem(newShape, columna3, color);

		xPos = rand() % 180 - 90;
		//float yPos = rand() % 81 + 10;
		zPos = rand() % 101 - 50;
		newShape = CreateShape(PxBoxGeometry(5, 8, 5), nullptr);
		columna4 = physics->createRigidStatic({ xPos, 9, zPos });
		columna4->attachShape(*newShape);
		scene->addActor(*columna4);
		renderNewBlock = new RenderItem(newShape, columna4, color);

		xPos = rand() % 180 - 90;
		//float yPos = rand() % 81 + 10;
		zPos = rand() % 101 - 50;
		newShape = CreateShape(PxBoxGeometry(5, 8, 5), nullptr);
		columna5 = physics->createRigidStatic({ xPos, 9, zPos });
		columna5->attachShape(*newShape);
		scene->addActor(*columna5);
		renderNewBlock = new RenderItem(newShape, columna5, color);


		//PxShape* shape10 = CreateShape(PxBoxGeometry(100, 100, 1), nullptr); //Delante

		solidViento = new SolidBodyWind(Vector3(0, 0, 0));
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

	void addExplosionForceRegistry(/*SolidBodyExplosion* generator, const std::vector<SolidBody*>& _bodies*/) {
		solidExplosion = new SolidBodyExplosion(200000, 50000, 100, { 0,0,0 });
		for (auto b : bodies) {
			forceRegistry.addRegistry(solidExplosion, b);
			b->bodyExplosionForce = solidExplosion;
		}
	};

	void addForceRegistry(RigidForceGenerator* generator, const std::vector<SolidBody*>& _bodies) {
		for (auto b : _bodies) {
			forceRegistry.addRegistry(generator, b);
		}
	};

	void setViento(const Vector3 windF) { solidViento->setWindForce(windF); }

	void shootRigid(Vector3 _vel, PxTransform _pos);
};

