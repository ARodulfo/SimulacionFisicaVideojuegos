#pragma once
#include "ParticleDragGenerator.h"

class WindGenerator : public ParticleDragGenerator
{
public:
	WindGenerator() {};
	WindGenerator(const float k1, const float k2, Vector3 wVel) : _k1(k1), _k2(k2), windVelocity(wVel) {};
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1, const float k2) { _k1 = k1; _k2 = k2; }
	inline void setWindVelocity(Vector3 wVel) { windVelocity = wVel; }
	inline float getK1() { return (_k1); }
	inline float getK2() { return (_k2); }
	inline Vector3 getWindVelocity() { return (windVelocity); }

protected:
	float _k1; //Coef for velocity
	float _k2; //Coef for square velocity
	Vector3 windVelocity; //Velocidad del viento

};

