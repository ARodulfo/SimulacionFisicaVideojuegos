#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 _pos_width, Vector3 _vel_width, std::string name, Vector3 mean_pos, Vector3 mean_vel, int num_particles, double partVida, double genProb, Vector3 aSpace) : ParticleGenerator(name, mean_pos, mean_vel, num_particles, partVida, aSpace)
{
    pos_width = _pos_width;
    vel_width = _vel_width;
    _generation_probability = genProb;
}

UniformParticleGenerator::~UniformParticleGenerator()
{
}

std::list<Particle*> UniformParticleGenerator::generateParticles()
{
    std::list<Particle*> listaParticulas;


    for (int i = 0; i < _num_particles; i++) {
        float probabilidadParticula = d(gen);

        if (probabilidadParticula > _generation_probability) {
            Vector3 auxVel;
            auxVel.x = (_mean_vel.x + vel_width.x / 2) * d(gen) + (_mean_vel.x - vel_width.x / 2);
            auxVel.y = (_mean_vel.y + vel_width.y / 2) * d(gen) + (_mean_vel.y - vel_width.y / 2);
            auxVel.z = (_mean_vel.z + vel_width.z / 2) * d(gen) + (_mean_vel.z - vel_width.z / 2);

            Vector3 auxPos;
            auxPos.x = (_mean_pos.x + pos_width.x / 2) * d(gen) + (_mean_pos.x - pos_width.x / 2);
            auxPos.y = (_mean_pos.y + pos_width.y / 2) * d(gen) + (_mean_pos.y - pos_width.y / 2);
            auxPos.z = (_mean_pos.z + pos_width.z / 2) * d(gen) + (_mean_pos.z - pos_width.z / 2);

            Particle* newParticle = new Particle(auxPos, auxVel, { 0.0,0.0,0.0 }, 0.99, 100, _gravity, new RenderItem(CreateShape(physx::PxSphereGeometry(2.0)), Vector4(1, 1, 1, 1)), _tVida, true, actionSpace);

            listaParticulas.push_back(newParticle);
        }
    }
    return listaParticulas;
}

void UniformParticleGenerator::generateUniformNumbers(Vector3 _std_dev_vel, Vector3 mean_vel, Vector3& resultVel)
{
    resultVel.x = (_mean_pos.x + pos_width.x / 2) * d(gen) + (_mean_pos.x - pos_width.x / 2);
    //resultVel.y = (_mean_pos.y + pos_width.y / 2) * d(gen) + (_mean_pos.y - pos_width.y / 2);
    resultVel.z = (_mean_pos.z + pos_width.z / 2) * d(gen) + (_mean_pos.z - pos_width.z / 2);
}
