#include "Proyectil.h"
#include "RenderUtils.hpp"


Proyectil::Proyectil(Vector3 posicion, Vector3 velocidad, Vector3 aceleracion, double damp, float masa, tipoBala bala) {

	switch (bala) {
	case CAÑON:
		setPos(posicion);
		setMass(masa);
		setVel(velocidad);
		setAcel(aceleracion);
		setDamp(damp);
		break;
	
	
	}
}