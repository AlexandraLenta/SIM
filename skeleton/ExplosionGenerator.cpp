#include "ExplosionGenerator.h"
#include <numbers>

ExplosionGenerator::ExplosionGenerator(Vector3D center, float r, float tCt, float k, float sV) : _radius(r), _timeConstant(tCt), _intensity(k), _timeSinceExplosion(0), _active(false), _explosionVel(sV) {

}

void ExplosionGenerator::applyForceToParticle(Particle* p, double t) {
	if (_active) {
		if (_explosionVel > 0)
			_radius = _timeSinceExplosion * _explosionVel;
		
		Vector3D particlePos = p->position.p;

		float r = sqrt(pow(particlePos.x() - _center.x(), 2) + pow(particlePos.y() - _center.y(), 2) + pow(particlePos.z() - _center.z(), 2));

		if (r < _radius) {
			Vector3D forceToApply = (particlePos - _center) * (_intensity / (r * r)) * pow(std::numbers::e, -_timeSinceExplosion / _timeConstant);

			p->applyForce(forceToApply);
		}

	}
}

void ExplosionGenerator::applyForce(std::vector<Particle*> p, double t) {
	ForceGenerator::applyForce(p, t);

	_timeSinceExplosion += t;

	if (_timeSinceExplosion >= 4.f * _timeConstant) {
		_active = false;
	}

}

void ExplosionGenerator::explode() {
	_active = true;
	_timeSinceExplosion = 0;
}