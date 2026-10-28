#include "BuoyancyGenerator.h"

BuoyancyGenerator::BuoyancyGenerator(float h, float V, float d) : ForceGenerator(), _height(h), _volume(V), _liquidDensity(d) {
	// TODO: create liquid particle
}

void BuoyancyGenerator::applyForceToParticle(Particle* p, double t) {
	float h = p->position.p.y;
	float h0 = _liquidParticle->position.p.y;

	Vector3D force(0, 0, 0);

	float immersed = 0.0f;

	if (h - h0 > _height * 0.5) {
		immersed = 0.0f;
	}
	else if (h0 - h > _height * 0.5) {
		immersed = 1.0f;
	}
	else {
		immersed = (h0 - h) / _height * 0.5f;
	}

	force.setY(_liquidDensity * _volume * immersed * _gravity);
	
	p->applyForce(force);
}