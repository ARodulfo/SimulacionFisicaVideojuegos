#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringForceGenerator : public SpringForceGenerator 
{
public: 
	AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr)
	{ _other = new Particle(anchor_pos, {0,0,0}, {0,0,0},0.99,0,0, new RenderItem(CreateShape(physx::PxBoxGeometry(4.0, 4.0, 4.0)), Vector4(1, 1, 1, 1)), 1000000, true, {1000,1000,1000}); }
	~AnchoredSpringForceGenerator();
};

