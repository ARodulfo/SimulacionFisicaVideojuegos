#pragma once
#include "WindGenerator.h"

class WhirlwindGenerator : public WindGenerator
{
public:
	WhirlwindGenerator() {};
	WhirlwindGenerator(const float k1, const float k2, Vector3 wOrigin, float wForce) : _k1(k1), _k2(k2), whirlwindOrigin(wOrigin), whirlwindForce(wForce) {};
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1, const float k2) { _k1 = k1; _k2 = k2; }
	inline void setOrigin(Vector3 origin) { whirlwindOrigin = origin;}
	inline void setForce(float force) { whirlwindForce = force; }
	inline float getK1() { return (_k1); }
	inline float getK2() { return (_k2); }
	inline Vector3 getOrigin() { return (whirlwindOrigin); }
	inline float getForce() { return (whirlwindForce); }

protected:
	float _k1; //Coef for velocity
	float _k2; //Coef for square velocity
	Vector3 whirlwindOrigin; //Origen del torbellino
	float whirlwindForce; //Constante de la fuerza del torbellino.
};

