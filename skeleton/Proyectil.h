#pragma once
 #include "Particle.h"


enum tipoBala {CA�ON, PISTOLA};

class Proyectil : public Particle
{
public:
	Proyectil::Proyectil(tipoBala bala);
	~Proyectil();
};

