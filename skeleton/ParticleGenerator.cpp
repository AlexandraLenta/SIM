#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Particle& config) : _config(config) {
}

void ParticleGenerator::setActive(bool a) {
	_isActive = a;
}

bool ParticleGenerator::isActive() {
	return _isActive;
}

std::vector<Particle*> update(double dt) {

}