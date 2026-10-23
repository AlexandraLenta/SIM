#include "GravityGenerator.h"



GravityGenerator::GravityGenerator(Vector3D gravity) : ForceGenerator(), _gravity(gravity) {

}

void GravityGenerator::applyForce(std::vector<Particle*> p, double t) {
	for (auto particle : p) {
		applyForceToParticle(particle, t);
	}
}

void GravityGenerator::applyForceToParticle(Particle* p, double t) {
	double s = p->simulatedSpeed / p->realSpeed;
	
	Vector3D simG = _gravity * (s * s);
	
	p->applyForce(p->simulatedMass * simG);
}

void GravityGenerator::setGravity(Vector3D acc) {
	_gravity = acc;
}

Vector3D GravityGenerator::getGravity() {
	return _gravity;
}