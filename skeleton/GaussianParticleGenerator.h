#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <list>


class GaussianParticleGenerator : public ParticleGenerator
{
private:
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<float> d{0,1};

	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
	float _gravity = -10.0;


public:
	GaussianParticleGenerator(Vector3 _std_dev_pos, Vector3 _std_dev_vel, std::string name, Vector3 mean_pos, Vector3 mean_vel, int num_particles, double partVida, Vector3 aSpace);
	~GaussianParticleGenerator();
	std::list<Particle*> generateParticles() override;


};

