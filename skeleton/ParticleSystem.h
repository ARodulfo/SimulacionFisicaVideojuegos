#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Firework.h"
#include <string>



class ParticleSystem 
{
private:
	std::list<Particle*> _particles;
	std::list<Firework*> _fireworks;
	std::list<ParticleGenerator*> _particle_generators;
	std::vector<FireworkRule> _firework_rules;

public:
	ParticleSystem();
	void update(double t);
	void addGenerator(ParticleGenerator* gen);
	ParticleGenerator* getParticleGenerator(std::string name);
	void createFireworkRules();
	std::vector<FireworkRule> getFireworkRules();
	void generateFirework(FireworkRule reglaFirework);
};