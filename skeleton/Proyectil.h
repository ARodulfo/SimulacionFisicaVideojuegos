#pragma once
 #include "Particle.h"


enum tipoBala {CAÑON, PISTOLA};

class Proyectil : public Particle
{
public:
	Proyectil::Proyectil(Vector3 posicion, Vector3 velocidad, Vector3 aceleracion, double damp, float masa, tipoBala bala);
};

