#include "Proyectil.h"
#include "RenderUtils.hpp"


Proyectil::Proyectil(tipoBala bala) {

	switch(bala) {
	case CAÑON:
		vel = GetCamera()->getEye();
		pose = GetCamera()->getTransform();
		acel = { 1.1, 1.1,1.1 };
		damping = 0.999;
		mass = 100;

		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pose, { 1.0,1.0,1.0,1.0 });
		//new Particle(GetCamera()->getEye(), GetCamera()->getDir(), 0.99, 200);
		break;

	case PISTOLA:
		vel = GetCamera()->getEye();
		pose = GetCamera()->getTransform();
		acel = { 1.1, 1.1,1.1 };
		damping = 0.999;
		break;

	}

}