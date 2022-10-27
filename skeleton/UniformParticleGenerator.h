#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <list>

class UniformParticleGenerator : public ParticleGenerator
{
private:
	std::random_device rd{};
	std::mt19937 gen{rd()};
	std::uniform_real_distribution<float> d{ 0,1 };

	Vector3 pos_width, vel_width;
	//double std_dev_t;
	float _gravity = -10.0;

public:
	UniformParticleGenerator(Vector3 _std_dev_pos, Vector3 _std_dev_vel, std::string name, Vector3 mean_pos, Vector3 mean_vel, int num_particles, double partVida, double genProb, Vector3 aSpace);
	~UniformParticleGenerator();
	std::list<Particle*> generateParticles() override;
};

