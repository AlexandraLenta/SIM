#include "Projectile.h"

Projectile::Projectile(Vector3D pos, Vector3D vel, Vector3D a, float mR, float d) : Particle(pos, vel, a, d) {

}

void Projectile::changeRealMass(float amount) {
	_realMass += amount;
	calculateSimulatedValues();
}

void Projectile::calculateSimulatedValues() {
	const float squaredVelDivision = (_realSpeed / _simulatedSpeed) * (_realSpeed / _simulatedSpeed);
	_simulatedMass = _realMass * squaredVelDivision;

	_simulatedGravity = _realGravity * squaredVelDivision;
}