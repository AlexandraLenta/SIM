#include "Projectile.h"

Projectile::Projectile() : Particle(1.0f, Vector4(1, 1, 1, 1)) {
	renderItem->visible = false;
}

Projectile::~Projectile() {

}

void Projectile::changeRealSpeed(float amount) {
	realSpeed += amount;
	calculateSimulatedValues();
}

void Projectile::shoot(physx::PxTransform origin, Vector3D dir) {
	position = origin;
	prevPosition = position;

	renderItem->visible = true;

	velocity = dir.normalized() * simulatedSpeed;
}