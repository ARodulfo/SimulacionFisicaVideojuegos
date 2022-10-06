#pragma once
 #include "Particle.h"


enum tipoBala {CA�ON, PISTOLA};

class Proyectil : public Particle
{
public:
	Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, tipoBala bala, RenderItem* ri);
	~Proyectil();
};

