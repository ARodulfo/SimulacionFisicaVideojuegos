#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 _std_dev_pos, Vector3 _std_dev_vel, std::string name, Vector3 mean_pos, Vector3 mean_vel, int num_particles, double partVida, Vector3 aSpace, Vector3 posIni, bool randomPos) : ParticleGenerator(name, mean_pos, mean_vel, num_particles, partVida, aSpace)
{
    std_dev_pos = _std_dev_pos;
    std_dev_vel = _std_dev_vel;
    initialPos = posIni;
    rPos = randomPos;
}

GaussianParticleGenerator::~GaussianParticleGenerator()
{
}

std::list<Particle*> GaussianParticleGenerator::generateParticles()
{
    std::list<Particle*> listaParticulas;
    Particle* newParticle;

    for (int i = 0; i < _num_particles; i++) {
        Vector3 auxVel;
        auxVel.x = std_dev_vel.x * d(gen) + _mean_vel.x;
        auxVel.y = std_dev_vel.y * d(gen) + _mean_vel.y;
        auxVel.z = std_dev_vel.z * d(gen) + _mean_vel.z;
        if (rPos) {
            Vector3 auxPos;
            auxPos.x = std_dev_pos.x * d(gen) + _mean_pos.x;
            auxPos.y = std_dev_pos.y * d(gen) + _mean_pos.y;
            auxPos.z = std_dev_pos.z * d(gen) + _mean_pos.z;

            newParticle = new Particle(auxPos, auxVel, { 0.0,0.0,0.0 }, 0.99, 100, _gravity, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(0, 0, 1, 1)), _tVida, true, actionSpace);
        }
        else {
            newParticle = new Particle(initialPos, auxVel, { 0.0,0.0,0.0 }, 0.99, 100, _gravity, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(0, 0, 0, 1)), _tVida, true, actionSpace);
        }
        

        listaParticulas.push_back(newParticle);
    }
    return listaParticulas;
}
