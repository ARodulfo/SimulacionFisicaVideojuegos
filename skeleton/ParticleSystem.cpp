#include "ParticleSystem.h"
#include "GaussianParticleGenerator.h"

ParticleSystem::ParticleSystem() {
	createFireworkRules();
}

void ParticleSystem::update(double t) {
	for (auto gen : _particle_generators) 
	{
		if (gen != NULL) {
			auto particleList = gen->generateParticles();
			for (auto particula : particleList) {
				_particles.push_back(particula);
			}
		}
	}
	forceRegistry.updateForces(t);
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

}

void ParticleSystem::addGenerator(ParticleGenerator* gen) {
	_particle_generators.push_back(gen);
}

void ParticleSystem::createFireworkRules()
{
	_firework_rules = std::vector<FireworkRule>(3);

	_firework_rules[0].set(PARTICULAS_CIRCULO, 2, 2, 0.999, 15, { 5, 5, 5 }, { 2, 2, 2 }, 2.25);
	_firework_rules[1].set(GENERADOR, 8, 2, 0.999, 1, { 7, 7, 7 }, { 2, 2, 2 }, 1);
	_firework_rules[2].set(FIREWORK, 2, 2, 0.999, 3, { 2, 10, 2 }, { 2, 2, 2 }, 1);
}

std::vector<FireworkRule> ParticleSystem::getFireworkRules()
{
	return _firework_rules;
}

void ParticleSystem::generateFirework(FireworkRule reglaFirework)
{
	_fireworks.push_back(new Firework({ 2,0,1 }, { 14.0,22.0,1.0 }, { 0.0,0.0,0.0 }, 0.99, 100, -5, reglaFirework, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), 1, true, { 100.0,100.0,100.0 }, 2));
}
