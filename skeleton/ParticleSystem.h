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

	ParticleGenerator* addGenerator(std::unique_ptr<ParticleGenerator> g);
	ForceGenerator* addForceGenerator(std::unique_ptr<ForceGenerator> f);

	void burst(int n, int index);

	// Return out a pooled particle ( + mark it as alive), or nullptr if the pool is full.
	Particle* spawn();

private:
	std::vector<Particle>  _pool;     // fixed size
	std::vector<Particle*> _active;   // currently alive
	std::vector<Particle*> _free;     // available for reuse

	std::vector<std::unique_ptr<ParticleGenerator>> _generators;
	std::vector<std::unique_ptr<ForceGenerator>>    _forceGenerators;

	void updateGenerators(double t);
	void updateParticles(double t);
	void applyForces(double t);

	void emitFrom(ParticleGenerator& g, int n);
};