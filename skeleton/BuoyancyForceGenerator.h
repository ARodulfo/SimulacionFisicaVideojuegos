#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float V, float d) : _height(h), _volume(V), _liquid_density(d) {};

	virtual void updateForce(Particle* particle, double t);
	void addRepresentationParticle(Particle* particle) { _liquid_particle = particle; }

	virtual ~BuoyancyForceGenerator() {};
protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;
	
	Particle* _liquid_particle;;
};

