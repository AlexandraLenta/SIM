#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3D windVel, Vector3D volumeCenter, Vector3D volumeExtents, float k1, float k2) : ForceGenerator(), _velocity(windVel), _k1(k1), _k2(k2), _center(volumeCenter), _extents(volumeExtents) {

}

void WindGenerator::applyForceToParticle(Particle* p, double t) {
	if (isInsideVolume(p->position.p)) {
		Vector3D diff = _velocity - p->velocity;

		Vector3D forceToApply = diff * _k1 + diff * diff.magnitude() * _k2;

		p->applyForce(forceToApply);
	}
}

//𝐹𝑣⃗⃗⃗ = 𝑘1(𝑣 𝑣 − 𝑣) + 𝑘2‖𝑣 𝑣 − 𝑣 ‖(𝑣 𝑣 − 𝑣)

bool WindGenerator::isInsideVolume(Vector3D pos) const {
	Vector3D extentsPositive = _center + _extents;
	Vector3D extentsNegative = _center - _extents;

	return pos.x() <= extentsPositive.x() && pos.x() >= extentsNegative.x()
		&& pos.y() <= extentsPositive.y() && pos.y() >= extentsNegative.y()
		&& pos.z() <= extentsPositive.z() && pos.z() >= extentsNegative.z();
}

TornadoGenerator::TornadoGenerator(Vector3D centerPos, Vector3D volume, float strength, float upStrength, float k1, float k2) : WindGenerator({ 0, 0, 0 }, centerPos, volume, k1, k2), _strength(strength), _upStrength(upStrength) {
}

void TornadoGenerator::applyForceToParticle(Particle* p, double t) {
	if (isInsideVolume(p->position.p)) {
		Vector3D vel = Vector3D {
			-(p->position.p.z - _center.z()),
			_upStrength - (p->position.p.y - _center.y()),
			p->position.p.x - _center.x()
		} * _strength;

		Vector3D diff = vel - p->velocity;

		Vector3D forceToApply = diff * _k1 + diff * diff.magnitude() * _k2;

		p->applyForce(forceToApply);
	}
}