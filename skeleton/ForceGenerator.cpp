#include "ForceGenerator.h"

void ForceGenerator::applyForce(std::vector<Particle*> p, double t) {
	if (_isActive) {
		for (auto particle : p) {
			applyForceToParticle(particle, t);
		}
	}
}

void ForceGenerator::setActive(bool a) {
	_isActive = a;
}

bool ForceGenerator::getActive() {
	return _isActive;
}