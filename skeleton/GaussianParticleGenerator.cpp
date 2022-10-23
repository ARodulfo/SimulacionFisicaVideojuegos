#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 _std_dev_pos, Vector3 _std_dev_vel)
{
    std_dev_pos = _std_dev_pos;
    std_dev_vel = _std_dev_vel;
}

std::list<Particle*> GaussianParticleGenerator::generateParticles()
{
    return ;
}
