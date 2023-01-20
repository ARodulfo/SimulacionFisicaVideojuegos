#include "ParticleSystem.h"
#include "GaussianParticleGenerator.h"
#include <iostream>

ParticleSystem::ParticleSystem() {
	createFireworkRules();
	gravityGen = new GravityForceGenerator({ 0,150,0 });
	windGen = new WindGenerator(0.7, 0.7, { 0,0,50 });
	numberGenerator = new UniformParticleGenerator({ 1.5,1.5,1.5 }, { 3.0,3.0,3.0 }, "fuente", { 1.0,1.0,1.0 }, { 10.0,25.0,2.0 }, 1, 2, 0.5, { 1000.0,1000.0,1000.0 });
}

void ParticleSystem::update(double t) {
	
	
	std::list<Particle*>::iterator it = _particles.begin();
	while (it != _particles.end())
	{

		if (*it != NULL) {
			(*it)->integrate(t);
			if (!(*it)->getViva())
			{

				/*auto cast = dynamic_cast<Firework*>(*it);
				if (cast != nullptr) {
					auto a = cast->explode(_firework_rules[0]);
					if (a.size() > 0)_particles.insert(_particles.begin(), a.begin(), a.end());
					a.clear();
				}*/
				if (*it != nullptr) {
					delete* it;
					it = _particles.erase(it);
				}
			}
			else it++;
		}
	}
	std::list<Firework*>::iterator it2 = _fireworks.begin();
	while (it2 != _fireworks.end())
	{

		if (*it2 != NULL) {
			(*it2)->integrate(t);
			if (!(*it2)->getViva())
			{
				auto a = (*it2)->explode(_firework_rules[0], _fireworks);
				switch ((*it2)->getReglaActual()._tipo)
				{
				case (PARTICULAS_CIRCULO):
					if (a.size() > 0)_particles.insert(_particles.begin(), a.begin(), a.end());
					a.clear();
					break;
				case (GENERADOR):
				{
					GaussianParticleGenerator* gaussianGen = new GaussianParticleGenerator({ 1.5,1.5,1.5 }, { 3.0,3.0,3.0 }, "fuente", { 1.0,1.0,1.0 }, { 10.0,25.0,2.0 }, 1, 5, { 1000.0,1000.0,1000.0 }, (*it2)->getPose().p, false);
					addGenerator(gaussianGen);
					break;
				}
				case (FIREWORK):
					
					break;
				default:
					break;
				}
					
				/*auto cast = dynamic_cast<Firework*>(*it);
				if (cast != nullptr) {
					auto a = cast->explode(_firework_rules[0]);
					if (a.size() > 0)_particles.insert(_particles.begin(), a.begin(), a.end());
					a.clear();
				}*/
				if (*it2 != nullptr) {
					delete* it2;
					it2 = _fireworks.erase(it2);
				}
			}
			else it2++;
		}
	}
	timeSinceLastLeak += t;
	forceRegistry.updateForces(t);
	for (auto gen : _particle_generators)
	{
		if (gen != NULL) {
			if (gen->getType() != LEAK) {
				auto particleList = gen->generateParticles();
				for (auto particula : particleList) {
					_particles.push_back(particula);
					addForceRegistry(windGen, particula);
				}
			}
			else {
				if (timeSinceLastLeak > step) {
					auto leakList = gen->generateParticles();
					for (auto particula : leakList) {
						_particles.push_back(particula);
						addForceRegistry(gravityGen, particula);
						//addForceRegistry(windGen, particula);
						timeSinceLastLeak = 0;
					}
				}
			}
			
		}
	}
	if (activeFireworkFountain) {
		generateFirework(getFireworkRules()[2]);
	}

}

void ParticleSystem::addGenerator(ParticleGenerator* gen) {
	_particle_generators.push_back(gen);
}

void ParticleSystem::addParticleWithForce(ForceGenerator* generator, Particle* particula)
{
	_particles.push_back(particula);
	forceRegistry.addRegistry(generator, particula);
}

void ParticleSystem::createFireworkRules()
{
	_firework_rules = std::vector<FireworkRule>(3);

	_firework_rules[0].set(PARTICULAS_CIRCULO, 1, 1, 0.999, 5, { 5, 5, 5 }, { 2, 2, 2 }, 1);
	_firework_rules[1].set(GENERADOR, 8, 2, 0.999, 1, { 7, 7, 7 }, { 2, 2, 2 }, 1);
	_firework_rules[2].set(FIREWORK, 2, 2, 0.999, 3, { 2, 10, 2 }, { 2, 2, 2 }, 1);
}

std::vector<FireworkRule> ParticleSystem::getFireworkRules()
{
	return _firework_rules;
}

void ParticleSystem::generateFirework(FireworkRule reglaFirework)
{
	Vector3 newVel = { 0,10.0, 0 };
	numberGenerator->generateUniformNumbers(Vector3(3.0, 3.0, 3.0), Vector3(10.0,25.0,2.0), newVel);
	//1.5,1.5,1.5 }, { 3.0,3.0,3.0 }, "fuente", { 1.0,1.0,1.0 }, { 10.0,25.0,2.0 }
	_fireworks.push_back(new Firework({ 0,5,-45}, newVel, { 0.0,0.0,0.0 }, 0.99, 100, -5, reglaFirework, new RenderItem(CreateShape(physx::PxSphereGeometry(1)), Vector4(1, 1, 1, 1)), 1, true, { 100.0,100.0,100.0 }, 2));
}

void ParticleSystem::removeParticles()
{
	std::list<Particle*>::iterator it = _particles.begin();
	while (it != _particles.end())
	{

		if (*it != NULL) {
					delete* it;
					it = _particles.erase(it);
		}
			else it++;
		
	}
}
