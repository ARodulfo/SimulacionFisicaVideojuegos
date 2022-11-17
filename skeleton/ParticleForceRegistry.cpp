#include "ParticleForceRegistry.h"

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p)
{
	this->insert(FRPair(fg, p));
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p)
{
	for (auto it = begin(); it != end(); it++) {
		if (it->second == p) it = this->erase(it);
	}
}
