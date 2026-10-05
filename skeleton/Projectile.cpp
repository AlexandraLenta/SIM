#include "Projectile.h"
#include <iostream>

Projectile::Projectile(Vector3D pos, float mR, float sR, float sS, float d) : Particle(pos), _realMass(mR), _realGravity(9.8f), _realSpeed(sR), _simulatedSpeed(sS) {
	calculateSimulatedValues();
}

Projectile::~Projectile() {

}

void Projectile::changeRealMass(float amount) {
	_realMass += amount;
	calculateSimulatedValues();
}

void Projectile::calculateSimulatedValues() {

	_simulatedMass = _realMass * ((_realSpeed / _simulatedSpeed) * (_realSpeed / _simulatedSpeed));
	
	_simulatedGravity = _realGravity * ((_simulatedSpeed / _realSpeed) * (_simulatedSpeed / _realSpeed));
}

void Projectile::integrateEulerSemiImplicit(double t) {
	_a = { 0, -_simulatedGravity, 0 }; // resetear la aceleracion a la gravedad

	Particle::integrateEulerSemiImplicit(t);
}

void Projectile::shoot(physx::PxTransform origin, Vector3D dir) {
	_pose = origin;
	_previousPose = _pose;

	_vel = dir.normalized() * _simulatedSpeed;
}