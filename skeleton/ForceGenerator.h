#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator() = default;

	void virtual applyForce(std::vector<Particle*> p, double t);

	void virtual applyForceToParticle(Particle* p, double t) = 0;
};

