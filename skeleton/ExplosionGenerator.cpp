#include "ExplosionGenerator.h"

ExplosionGenerator::ExplosionGenerator(Vector3D center, float r, float tCt, float k) : _radius(r), _timeConstant(tCt), _intensity(k) {

}

void ExplosionGenerator::applyForceToParticle(Particle* p, double t) {

	Vector3D particlePos = p->position.p;

	if (isInsideVolume(particlePos)) {

		float r = sqrt(pow(particlePos.x() - _center.x(), 2) + pow(particlePos.y() - _center.y(), 2) + pow(particlePos.z() - _center.z(), 2));

		Vector3D forceToApply = (particlePos - _center) * (_intensity / (r * r))*;

	}
}