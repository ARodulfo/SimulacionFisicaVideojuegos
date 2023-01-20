#include "SolidBodyWind.h"

void SolidBodyWind::updateForce(SolidBody* body, float t)
{
	body->force += windForce;
}