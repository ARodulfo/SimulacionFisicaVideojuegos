#pragma once
 #include "Particle.h"


typedef enum tipoBala {CAÑON, PISTOLA};

class Proyectil : public Particle
{
public:
	Proyectil::Proyectil(tipoBala bala);
};

