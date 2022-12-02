#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include <iostream>
#include <vector>

class SpringForceGenerator : public ForceGenerator
{
public :
	SpringForceGenerator(double k, double resting_length, Particle* other) : _k(k), _resting_length(resting_length), _other(other) {};
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double k) { _k = k; }
	virtual ~SpringForceGenerator() {}
protected:
	double _k; //Coeficiente elástico
	double _resting_length;
	Particle* _other;
};