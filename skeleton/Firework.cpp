#include "Firework.h"

Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, float Gravity, FireworkRule regla, RenderItem* ri, double tVida, bool viva, Vector3 aSpace, int fireworkGenerations) : Particle(Pos, Vel, Acel, Damping, Mass, Gravity, ri, tVida, viva, aSpace)
{
	_reglaFirework = regla;
	generations = fireworkGenerations;
	//tiempoVida = regla._std_dev_lifeTime * d(gen) + regla._mean_lifeTime;
}

std::list<Particle*> Firework::explode()
{
	std::list<Particle*>fireworkList;
	
	double tiempoVida = _reglaFirework._std_dev_lifeTime * d(gen) + _reglaFirework._mean_lifeTime;
	int offset = 1.2;
	Vector3 newPos = pose.p * offset;
	Vector4 color{ (float)dColor(gen),(float)dColor(gen),(float)dColor(gen),1 };
	if (generations > 0) {
		switch (_reglaFirework._tipo) {
		case (PARTICULAS_CIRCULO):
		{
			float anguloParticula = 1;
			float radioExplosion = 3;
			int circleOffset = 4.5;
			for (int i = 0; i < _reglaFirework._particleCount; i++)
			{
				Vector3 newDir1{ float(physx::PxCos(anguloParticula) * radioExplosion), float(0), float(physx::PxSin(anguloParticula) * radioExplosion) };
				newDir1 *= circleOffset;
				anguloParticula += 360 / _reglaFirework._particleCount;
				Particle* particle = new Particle(newPos, newDir1, { 0.5,0.5,0.5 }, 0.99, 100, -1, new RenderItem(CreateShape(physx::PxSphereGeometry(_reglaFirework.particleSize)), Vector4(1, 1, 1, 1)), tiempoVida, true, { 1000.0,1000.0,1000.0 });
				particle->setColor(color);
				fireworkList.push_back(particle);
				/*Vector3 dir2{ (float)normal(generator),(float)normal(generator),(float)normal(generator) };
				Vector4 colorRand{ (float)normal(generator),(float)normal(generator),(float)normal(generator),1 };
				Firework* p = new Firework(pos, dir2, { 0.5,0.5,0.5 }, 1, 0.99, new RenderItem(CreateShape(PxSphereGeometry(sizeF)), Vector4(1, 0, 1, 1)), sizeF, nGeneraciones - 1, colorRand, tAlive / 1.25, nPart, circulo);
				listExp.push_back(p);*/
			}
			break;
		}
		case (GENERADOR):
			break;
		case (FIREWORK):
			break;
		default:
			break;
		}
	}
	return fireworkList;
}

FireworkRule Firework::getReglaActual()
{
	return _reglaFirework;
}
