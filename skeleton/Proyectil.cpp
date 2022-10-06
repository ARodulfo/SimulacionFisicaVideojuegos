#include <iostream>
#include "Proyectil.h"
#include "RenderUtils.hpp"


Proyectil::Proyectil(tipoBala bala) : Particle() {

	switch (bala) {
	case CAÑON:
		std::cout << "Hola";
		setPos(GetCamera()->getTransform().p);
		setMass(300);
		setVel(GetCamera()->getDir().getNormalized() * 100);
		setAcel({ 0.0,0.0,9.0 });
		setDamp(0.99);
		setRender(renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pose, { 1.0,1.0,1.0,1.0 }) );

		break;
	defeult:
		break;
	}
}

Proyectil::~Proyectil()
{
	DeregisterRenderItem(renderItem);
}

//Vector3 posicion, Vector3 velocidad, Vector3 aceleracion, double damp, float masa,