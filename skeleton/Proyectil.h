#pragma once
 #include "Particle.h"


enum tipoBala {CAÑON, PISTOLA};

class Proyectil : public Particle
{
public:
	Proyectil::Proyectil(tipoBala bala);
	~Proyectil();
};

