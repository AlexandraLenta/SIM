#include "ParticleGenerator.h"
#include <numbers>

ParticleGenerator::ParticleGenerator(ParticleGenConfig config) : _config(config) {
	_mt = std::mt19937(std::random_device()());
}

void ParticleGenerator::setActive(bool a) {
	_isActive = a;
}

bool ParticleGenerator::isActive() {
	return _isActive;
}

std::vector<Particle*> ParticleGenerator::updateGenerate(double dt) {
	std::vector<Particle*> spawned = {};

	if (_isActive) {
		_timer += dt;

		while (_timer >= _spawnInterval) {
			_timer -= _spawnInterval;

			spawned.push_back(spawn());
		}
	}

	return spawned;
}

Particle* ParticleGenerator::spawn() {

	Particle* p = new Particle();

	p->position = physx::PxTransform(generateSpawnPosition());
	p->velocity = generateVelocity();

	p->calculateSimulatedValues();
	return p;
}

Vector3D ParticleGenerator::generateSpawnPosition() {
	switch (_config.originShape) {
		// generate from the same point
	case GeneratorOrigin::POINT: {
		return _config.originPoint;
	}

		// generate on a line
	case GeneratorOrigin::LINE: {
		return _config.originPoint +
			_config.axis.normalized() *
			generateUniform(-_config.shapeRadius, _config.shapeRadius);
	}

		// generate INSIDE sphere
	case GeneratorOrigin::INSIDE_SPHERE: {
		float y = generateUniform(-1, 1); // assume sphere in (0, 0, 0), with radius = 1

		float radiusAtY = sqrt(1 - y * y); // radius on xz plane at y
		float longitude = generateUniform(-std::numbers::pi_v<float>, std::numbers::pi_v<float>); // random longitude
		
		Vector3D pointOnSphere = { radiusAtY * std::sin(longitude),  // xyz on sphere surface
		y,
		radiusAtY * std::cos(longitude) };

		Vector3D in = pointOnSphere * (_config.shapeRadius * std::cbrt(generateUniform(0, 1))); // radius is cube root of random
			return _config.originPoint + in;
	}

		// generate on the SURFACE of the sphere
	case GeneratorOrigin::SURFACE_SPHERE: {
		float y = generateUniform(-1, 1); // assume sphere in (0, 0, 0), with radius = 1

		float radiusAtY = sqrt(1 - y * y); // radius on xz plane at y
		float longitude = generateUniform(-std::numbers::pi, std::numbers::pi); // random longitude

		Vector3D pointOnSphere = { radiusAtY * std::sin(longitude),  // xyz on sphere surface
		y,
		radiusAtY * std::cos(longitude) };

		return _config.originPoint + pointOnSphere * _config.shapeRadius;
	}

		// generate INSIDE box
	case GeneratorOrigin::BOX: {
		Vector3D pos = { generateUniform(-_config.boxHalfExtents.x(), _config.boxHalfExtents.x()),
						 generateUniform(-_config.boxHalfExtents.y(), _config.boxHalfExtents.y()),
						 generateUniform(-_config.boxHalfExtents.z(), _config.boxHalfExtents.z()) };
		return pos + _config.originPoint;
	}
	}

	return _config.originPoint;
}

Vector3D ParticleGenerator::generateVelocity() {
	switch (_config.spawnShape) {
	case GeneratorShape::LINE:
		return _config.meanVelocity;
	case GeneratorShape::CONE:
		return;
	}
}

float ParticleGenerator::generateUniform(float min, float max) {
	return _uniformDist(_mt, std::uniform_real_distribution<float>::param_type(min, max));
}

float ParticleGenerator::generateNormal(float mean, float stddev) {
	return _normalDist(_mt, std::normal_distribution<float>::param_type(mean, stddev));
}