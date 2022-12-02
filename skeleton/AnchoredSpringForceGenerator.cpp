#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
{
	delete _other;
}
