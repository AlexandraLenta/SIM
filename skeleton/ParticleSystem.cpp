#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : _pool(MAX_PARTICLES) {
	_active.reserve(MAX_PARTICLES);
	_free.reserve(MAX_PARTICLES);

	for (auto& p : _pool) {
		p.alive = false;
		_free.push_back(&p);
	}
}

ParticleSystem::~ParticleSystem() {
}

ParticleGenerator* ParticleSystem::addGenerator(std::unique_ptr<ParticleGenerator> g) {
	_generators.push_back(std::move(g));

	return _generators.back().get();
}

ForceGenerator* ParticleSystem::addForceGenerator(std::unique_ptr<ForceGenerator> f) {
	_forceGenerators.push_back(std::move(f));

	return _forceGenerators.back().get();
}

void ParticleSystem::emitFrom(ParticleGenerator& g, int n) {
	for (int i = 0; i < n; ++i) {
		Particle* p = spawn();
		if (!p) return; // if the pool is full
		
		g.initParticle(*p);
	}
}

Particle* ParticleSystem::spawn() {
	if (_free.empty()) return nullptr; // no more free particles

	Particle* p = _free.back();

	_free.pop_back();

	p->alive = true;
	
	_active.push_back(p); // move from free to active
	
	return p;
}

void ParticleSystem::burst(int n, int index) {
	if (index < _generators.size())
		emitFrom(*_generators[index], n);
}

void ParticleSystem::update(double t) {
	applyForces(t);
	updateParticles(t);
	updateGenerators(t); // IMPORTANT: keep last, so new particles are updated next frame (to get rid of _queuedParticles)
}

void ParticleSystem::applyForces(double t) {
	for (auto& fg : _forceGenerators) {
		fg->applyForce(_active, t);
	}
}

void ParticleSystem::updateParticles(double t) {
	for (int i = 0; i < _active.size();) {
		Particle* p = _active[i];
		p->update(t);

		if (!p->alive) {
			_free.push_back(p); // free up particle that just died
			_active[i] = _active.back(); // replace the dead particle with an active one
			_active.pop_back();
		}
		else {
			i++; // only advance i if we haven't swapped anything
		}
	}
}

void ParticleSystem::updateGenerators(double t) {
	for (auto& g : _generators)
		if (g->isActive())
			emitFrom(*g, g->update(t));
}