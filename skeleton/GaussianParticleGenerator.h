#pragma once
#include "ParticleGenerator.h"
#include <list>


class GaussianParticleGenerator : public ParticleGenerator
{
private:
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
public:
	GaussianParticleGenerator(Vector3 _std_dev_pos, Vector3 _std_dev_vel);
	std::list<Particle*> generateParticles() override;


};

