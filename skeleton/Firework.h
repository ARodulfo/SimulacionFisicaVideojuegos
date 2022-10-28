#pragma once
#include "Particle.h"
#include <list>
#include <random>

enum FireworkType { PARTICULAS_CIRCULO , GENERADOR, FIREWORK };

struct FireworkRule {
	FireworkType _tipo;
	float _mean_lifeTime, _std_dev_lifeTime;
	Vector3 _mean_vel, _std_dev_vel;
	float damping, particleSize;
	int _particleCount;

	void set(FireworkType tipo, float mean_lifeTIme, float std_dev_lifeTime, float damp, int count, Vector3 mean_vel, Vector3 std_dev_vel, float partSize) {
		_tipo = tipo;
		_mean_lifeTime = mean_lifeTIme;
		_std_dev_lifeTime = std_dev_lifeTime;
		damping = damp;
		_particleCount = count;
		_mean_vel = mean_vel;
		_std_dev_vel = std_dev_vel;
		particleSize = partSize;
	}
};


class Firework : public Particle
{
private:
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<float> d{ 0,1 };
	std::normal_distribution<float> dColor{ 5,9 };
	FireworkRule _reglaFirework;
	int generations;

public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, float Mass, float Gravity, FireworkRule regla, RenderItem* ri, double tVida, bool viva, Vector3 aSpace, int fireworkGenerations);
	std::list<Particle*> explode();
	FireworkRule getReglaActual();

};

