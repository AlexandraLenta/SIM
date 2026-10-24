#include "ForceGenerator.h"

void ForceGenerator::applyForce(std::vector<Particle*> p, double t) {
	for (auto particle : p) {
		applyForceToParticle(particle, t);
	}
}