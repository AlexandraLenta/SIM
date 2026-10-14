#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Particle config) : _particleConfig(config), _generators(), _queuedParticles(), _particles() {
}

ParticleSystem::~ParticleSystem() {
	for (auto p : _particles)
		delete p;
	for (auto g : _generators)
		delete g;
	for (auto q : _queuedParticles)
		delete q;

	_particles.clear();
	_generators.clear();
	_queuedParticles.clear();
}

void ParticleSystem::addGenerator(ParticleGenerator* g) {
	_generators.push_back(g);
}

void ParticleSystem::update(double t) {
	// add queued up particles to particle list
	_particles.insert(_queuedParticles.end(), _particles.begin(), _particles.end());
	_queuedParticles.clear();

	// update generators, queue up particles to add next frame
	for (auto g : _generators) {
		if (g->isActive()) {
			auto particles = g->updateGenerate(t);
			_queuedParticles.insert(_particles.end(), particles.begin(), particles.end());
		}
	}

	// update particles & remove if dead
	for (auto p = _particles.begin(); p != _particles.end();) {
		if ((*p)->alive) {
			(*p)->update(t);
		}
		else {
			p = _particles.erase(p);
		}
	}
}

// COULD DO THIS!
// find first dead particle, and then pass that particle/index to the generator update and generate to use that particle?