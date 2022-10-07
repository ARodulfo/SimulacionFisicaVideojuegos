#include <iostream>
#include "Proyectil.h"
#include "RenderUtils.hpp"


Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, tipoBala bala, RenderItem * ri) : Particle(Pos,  Vel,  Acel, Damping, Mass, ri) {

	switch (bala) {
	case CAÑON:
		std::cout << "Hola";
		setMass(300);
		setVel(vel * 100);
		setAcel({ 0.0,-50.0,0.0 });
		setDamp(0.99);
		//setRender(renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pose, { 1.0,1.0,1.0,1.0 }) );

		break;
	defeult:
		break;
	}
}

Proyectil::~Proyectil()
{

}

//Vector3 posicion, Vector3 velocidad, Vector3 aceleracion, double damp, float masa,