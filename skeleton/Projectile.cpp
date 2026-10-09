#include "Projectile.h"
#include <iostream>

Projectile::Projectile(Vector3D pos, float mR, float sR, float sS, float d) : Particle(pos, { 0, 0, 0 }, { 0, 0, 0 }, 0, { 1,1,1,1 }, mR, sR, sS, d) {
	
}

Projectile::~Projectile() {

}

void Projectile::changeRealSpeed(float amount) {
	_realSpeed += amount;
	calculateSimulatedValues();
}

void Projectile::shoot(physx::PxTransform origin, Vector3D dir) {
	_pose = origin;
	_previousPose = _pose;

	_vel = dir.normalized() * _simulatedSpeed;
}