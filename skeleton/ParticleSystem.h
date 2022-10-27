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
	ParticleSystem();
	void update(double t);
	void addGenerator(ParticleGenerator* gen);
	ParticleGenerator* getParticleGenerator(std::string name);

};