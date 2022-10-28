#include "Firework.h"

Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, float Gravity, FireworkRule regla, RenderItem* ri, double tVida, bool viva, Vector3 aSpace, int fireworkGenerations) : Particle(Pos, Vel, Acel, Damping, Mass, Gravity, ri, tVida, viva, aSpace)
{
	_reglaFirework = regla;
	generations = fireworkGenerations;
	//tiempoVida = regla._std_dev_lifeTime * d(gen) + regla._mean_lifeTime;
}

std::list<Particle*> Firework::explode(FireworkRule newRule, std::list<Firework*>& listaFireworks)
{
	std::list<Particle*>ParticleList;
	FireworkRule nuevaRegla = newRule;
	
	double tiempoVida = _reglaFirework._std_dev_lifeTime * d(gen) + _reglaFirework._mean_lifeTime;
	int offset = 1.2;
	Vector3 newPos = pose.p * offset;
	
	if (generations > 0) {
		switch (_reglaFirework._tipo) {
		case (PARTICULAS_CIRCULO):
		{
			float anguloParticula = 1;
			float radioExplosion = 3;
			int circleOffset = 4.5;
			for (int i = 0; i < _reglaFirework._particleCount; i++)
			{
				Vector4 color{ (float)dColor(gen),(float)dColor(gen),(float)dColor(gen),1 };
				Vector3 newDir1{ float(physx::PxCos(anguloParticula) * radioExplosion), float(0), float(physx::PxSin(anguloParticula) * radioExplosion) };
				newDir1 *= circleOffset;
				anguloParticula += 360 / _reglaFirework._particleCount;
				Particle* particle = new Particle(newPos, newDir1, { 0.5,0.5,0.5 }, 0.99, 100, -1, new RenderItem(CreateShape(physx::PxSphereGeometry(_reglaFirework.particleSize)), Vector4(1, 1, 1, 1)), tiempoVida, true, { 1000.0,1000.0,1000.0 });
				particle->setColor(color);
				ParticleList.push_back(particle);
				
				
			}
			break;
		}
		case (GENERADOR):
			break;
		case (FIREWORK):
			for (int i = 0; i < _reglaFirework._particleCount; i++)
			{
				Vector4 color{ (float)dColor(gen),(float)dColor(gen),(float)dColor(gen),1 };
				Vector3 newDir2{ _reglaFirework._std_dev_vel.x *(float)d(gen) + _reglaFirework._mean_vel.x,_reglaFirework._std_dev_vel.y * (float)d(gen) + _reglaFirework._mean_vel.y,_reglaFirework._std_dev_vel.z * (float)d(gen) + _reglaFirework._mean_vel.z };
				Firework* fireworks = new Firework(newPos, newDir2, { 0,0,0 }, 0.99, 100, -5, nuevaRegla,new RenderItem(CreateShape(physx::PxSphereGeometry(_reglaFirework.particleSize)), Vector4(1, 1, 1, 1)), tiempoVida, true, { 1000.0,1000.0,1000.0 }, generations-1);
				fireworks->setColor(color);
				listaFireworks.push_back(fireworks);
				
			}
			break;
		default:
			break;
		}
	}
	return ParticleList;
}

FireworkRule Firework::getReglaActual()
{
	return _reglaFirework;
}
