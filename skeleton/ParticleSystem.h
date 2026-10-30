#pragma once
#include "Vector3D.h"
#include <vector>
#include "ParticleGenerator.h"
#include "Particle.h"
#include "ForceGenerator.h"

class ParticleSystem
{
public:
	static constexpr size_t MAX_PARTICLES = 100;

	ParticleSystem();

	~ParticleSystem();

	void update(double t);

	void addGenerator(ParticleGenerator* g);
	void addForceGenerator(ForceGenerator* f);

	void burst(int n, int index);

private:
	std::vector<Particle*> _particles;
	std::vector<Particle*> _queuedParticles;
	std::vector<ParticleGenerator*> _generators;
	std::vector<ForceGenerator*> _forceGenerators;

	void updateParticleGenerators(double t);
	void updateParticles(double t);
	void applyForces(double t);
};
