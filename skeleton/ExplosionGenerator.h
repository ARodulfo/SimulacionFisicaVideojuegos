#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator() {};
	ExplosionGenerator(const float k1, const float k2, float radius, float blast, float time, Vector3 center) : _k1(k1), _k2(k2), explosionRadius(radius), explosionBlast(blast), timeConstant(time), explosionCenter(center) {};
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1, const float k2) { _k1 = k1; _k2 = k2; }
	inline void setRadius(float radius) { explosionRadius = radius; }
	inline void setBlast(float blast) { explosionBlast = blast; }
	inline void setTime(float time) { timeConstant = time; }
	inline void setCenter(Vector3 center) { explosionCenter = center; }
	inline float getK1() { return (_k1); }
	inline float getK2() { return (_k2); }
	inline float getRadius() { return (explosionRadius); }
	inline float getBlast() { return (explosionBlast); }
	inline float getTime() { return (timeConstant); }
	inline Vector3 getCenter() { return (explosionCenter); }

protected:
	float _k1; //Coef for velocity
	float _k2; //Coef for square velocity
	float explosionRadius; //Radio de explosion
	float explosionBlast; //Fuerza de la explosión
	float timeConstant; //Constante de tiempo
	Vector3 explosionCenter; //Centro de la explosión
};

