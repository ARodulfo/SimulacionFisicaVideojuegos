#pragma once
#include <string>
#include "core.hpp"
#include "Particle.h"
#include "Firework.h"
#include <list>

enum Generator_Type { LEAK, HUMO, NORMAL };

class ParticleGenerator
{
protected:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability = 0;
	double _tVida;
	int _num_particles;
	Vector3 actionSpace;
	Generator_Type tipo = NORMAL;

	//Particle* _model;

public:
	ParticleGenerator(std::string name, Vector3 pos, Vector3 vel, int particle_quantity, double partVida, Vector3 aSpace, Generator_Type _tipo = NORMAL) : _name(name), _mean_pos(pos), _mean_vel(vel), _num_particles(particle_quantity), _tVida(partVida), actionSpace(aSpace) {};
	//void setParticle(Particle* model);
	virtual std::list<Particle*> generateParticles() = 0;
	void setType(Generator_Type _tipo) { tipo = _tipo; }
	Generator_Type getType() { return tipo; }

};

