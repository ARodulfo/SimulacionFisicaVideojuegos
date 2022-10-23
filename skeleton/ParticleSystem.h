#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include <string>



class ParticleSystem 
{
private:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particle_generators;

public:
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);

};