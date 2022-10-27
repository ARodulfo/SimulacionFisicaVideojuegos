#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {

}

void ParticleSystem::update(double t) {
	for (auto gen : _particle_generators) {
		if (gen != NULL) {
			auto particleList = gen->generateParticles();
			for (auto particula : particleList) {
				_particles.push_back(particula);
			}
		}
	}
	std::list<Particle*>::iterator it = _particles.begin();
	while (it != _particles.end())
	{

		if (*it != NULL) {
			(*it)->integrate(t);
			if (!(*it)->getViva())
			{

				/*auto cast = dynamic_cast<Firework*>(*it);
				if (cast != nullptr) {
					auto a = cast->explode();
					if (a.size() > 0)particulasGen.insert(particulasGen.begin(), a.begin(), a.end());
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

}

void ParticleSystem::addGenerator(ParticleGenerator* gen) {
	_particle_generators.push_back(gen);
}