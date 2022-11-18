#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"
#include <string>



class ParticleSystem 
{
private:
	std::list<Particle*> _particles;
	std::list<Firework*> _fireworks;
	std::list<ParticleGenerator*> _particle_generators;
	std::vector<FireworkRule> _firework_rules;
	ParticleForceRegistry forceRegistry;

public:
	ParticleSystem();
	void update(double t);
	void addGenerator(ParticleGenerator* gen);
	void addParticle(Particle* particula) { _particles.push_back(particula); }
	void addForceRegistry(ForceGenerator* generator, Particle* particula) { forceRegistry.addRegistry(generator, particula); };
	ParticleGenerator* getParticleGenerator(std::string name);
	void createFireworkRules();
	std::vector<FireworkRule> getFireworkRules();
	void generateFirework(FireworkRule reglaFirework);
};