#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator() {};
	ExplosionGenerator(float radius, float blast, float time, Vector3 center) : explosionRadius(radius), explosionBlast(blast), timeConstant(time), explosionCenter(center) {};
	virtual void updateForce(Particle* particle, double t);
	inline void setRadius(float radius) { explosionRadius = radius; }
	inline void setBlast(float blast) { explosionBlast = blast; }
	inline void setTime(float time) { timeConstant = time; }
	inline void setCenter(Vector3 center) { explosionCenter = center; }
	inline float getRadius() { return (explosionRadius); }
	inline float getBlast() { return (explosionBlast); }
	inline float getTime() { return (timeConstant); }
	inline Vector3 getCenter() { return (explosionCenter); }

protected:
	float explosionRadius; //Radio de explosion
	float explosionBlast; //Fuerza de la explosión
	float timeConstant; //Constante de tiempo
	Vector3 explosionCenter; //Centro de la explosión
};

