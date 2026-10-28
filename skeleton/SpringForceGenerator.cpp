#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double restL, Particle* other) : ForceGenerator(), _k(k), _restingLength(restL), _otherParticle(other) {

}

void SpringForceGenerator::applyForceToParticle(Particle* p, double t) {
	Vector3D relativePos = _otherParticle->position.p - p->position.p;

	Vector3D force;

	const float length = relativePos.normalized().magnitude();
	const float deltaX = length - _restingLength;

	force = relativePos * deltaX * _k;

	p->applyForce(force);
}

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double restL, const Vector3D& anchorPos) : SpringForceGenerator(k, restL, nullptr) {
	_otherParticle = new Particle(0, {0, 0, 0, 0});
	_otherParticle->position = physx::PxTransform(anchorPos);
	_otherParticle->velocity = { 0, 0, 0 };
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {
	delete _otherParticle; _otherParticle = nullptr;
}