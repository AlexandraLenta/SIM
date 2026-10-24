#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3D windVel, Vector3D volumeCenter, Vector3D volumeExtents, float k1, float k2) : ForceGenerator(), _velocity(windVel), _k1(k1), _k2(k2), _center(volumeCenter), _extents(volumeExtents) {

}

void WindGenerator::applyForceToParticle(Particle* p, double t) {
	if (isInsideVolume(p->position.p)) {
		Vector3D diff = _velocity - p->velocity;

		//std::cout << diff << '\n';

		Vector3D forceToApply = diff * _k1 + diff * diff.magnitude() * _k2;

		//std::cout << forceToApply << '\n';

		p->applyForce(forceToApply);
	}
}

//𝐹𝑣⃗⃗⃗ = 𝑘1(𝑣 𝑣 − 𝑣) + 𝑘2‖𝑣 𝑣 − 𝑣 ‖(𝑣 𝑣 − 𝑣)

bool WindGenerator::isInsideVolume(Vector3D pos) {
	Vector3D extentsPositive = _center + _extents;
	Vector3D extentsNegative = _center - _extents;

	return pos.x() <= extentsPositive.x() && pos.x() >= extentsNegative.x()
		&& pos.y() <= extentsPositive.y() && pos.y() >= extentsNegative.y()
		&& pos.z() <= extentsPositive.z() && pos.z() >= extentsNegative.z();
}