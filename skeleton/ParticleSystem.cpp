#include "ParticleSystem.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator() {
	_g = NormalDistribution();
}

Particle* ParticleGenerator::generateParticle(Vector3D startingPos, Vector3D dir) {
	float speed = _g.generate();

	Particle* p = new Particle(startingPos);
	p->setRealSpeed(speed);

	return p;
}