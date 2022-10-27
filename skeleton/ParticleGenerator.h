#pragma once
#include <string>
#include "core.hpp"
#include "Particle.h"
#include <list>

class ParticleGenerator
{
protected:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability = 0;
	double _tVida;
	int _num_particles;
	Vector3 actionSpace;
	//Particle* _model;

public:
	ParticleGenerator(std::string name, Vector3 pos, Vector3 vel, int particle_quantity, double partVida, Vector3 aSpace) : _name(name), _mean_pos(pos), _mean_vel(vel), _num_particles(particle_quantity), _tVida(partVida), actionSpace(aSpace) {};
	//void setParticle(Particle* model);
	virtual std::list<Particle*> generateParticles() = 0;

};

