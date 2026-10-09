#pragma once
#include "Vector3D.h"
#include <vector>
#include "NormalDistribution.h"

class Particle;

class ParticleGenerator {
public:
	ParticleGenerator();
	Particle* generateParticle(Vector3D startingPos, Vector3D dir);

private:
	NormalDistribution _g;
};

class ParticleSystem
{
public:
	ParticleSystem(Vector3D pos, int nr = 100, float minSpeed = 0, float maxSpeed = 100, float lifetime = 10);

	void update(double t);

private:
	std::vector<Particle*> _particles;
	ParticleGenerator _gen;
};
