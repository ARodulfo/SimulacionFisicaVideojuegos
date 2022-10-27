#pragma once
 #include "Particle.h"


enum tipoBala {CAÑON, PISTOLA};

class Proyectil : public Particle
{
public:
	Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, float Gravity, tipoBala bala, RenderItem* ri, double tVida, bool viva, Vector3 aSpace);
	~Proyectil();
};