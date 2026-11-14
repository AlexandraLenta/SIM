#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double restL, Particle* first, Particle* second) : ForceGenerator(), _k(k), _restingLength(restL), _firstParticle(first), _secondParticle(second) {}

void SpringForceGenerator::applyForceToParticle(Particle* p, double t) {
	if (!_firstParticle->alive || !_secondParticle->alive) return;

	Vector3D relativePos = _secondParticle->position.p - _firstParticle->position.p;

	const float length = relativePos.magnitude();

	Vector3D force;

	const float deltaX = length - _restingLength;

	force = relativePos.normalized() * deltaX * _k;

	_firstParticle->applyForce(force);
	_secondParticle->applyForce({-force.x(), -force.y(), -force.z()});

}

void SpringForceGenerator::applyForce(std::vector<Particle*> p, double t) {
	if (_isActive) {
		applyForceToParticle(nullptr, t);
	}
}

void SpringForceGenerator::setK(double k) {
	_k = k;
}

double SpringForceGenerator::getK() {
	return _k;
}

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double restL, const Vector3D& anchorPos, Particle* first) : SpringForceGenerator(k, restL, first, nullptr) {
	_secondParticle = new Particle();
	_secondParticle->position = physx::PxTransform(anchorPos);
	_secondParticle->velocity = { 0, 0, 0 };
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {
	delete _secondParticle;
	_secondParticle = nullptr;
}
void AnchoredSpringForceGenerator::applyForceToParticle(Particle* p, double t) {
	if (!_firstParticle->alive || !_secondParticle->alive) return;

	Vector3D relativePos = _secondParticle->position.p - _firstParticle->position.p;

	const float length = relativePos.magnitude();

	Vector3D force;

	const float deltaX = length - _restingLength;

	force = relativePos.normalized() * deltaX * _k;

	_firstParticle->applyForce(force);
}

ElasticForceGenerator::ElasticForceGenerator(double k, double restL, Particle* first, Particle* second) : SpringForceGenerator(k, restL, first, second) {}

void ElasticForceGenerator::applyForceToParticle(Particle* p, double t) {
	if (!_firstParticle->alive || !_secondParticle->alive) return;

	Vector3D relativePos = _secondParticle->position.p - _firstParticle->position.p;

	const float length = relativePos.magnitude();
	
	// loose elastic
	if (length <= _restingLength) {
		return;
	}

	Vector3D force;

	const float deltaX = length - _restingLength;

	force = relativePos.normalized() * deltaX * _k;

	_firstParticle->applyForce(force);
	_secondParticle->applyForce({ -force.x(), -force.y(), -force.z() });
}