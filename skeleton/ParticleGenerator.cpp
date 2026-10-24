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

void ParticleGenerator::setSpawnInterval(double t) {
	_spawnInterval = t;
}

std::vector<Particle*> ParticleGenerator::updateGenerate(double dt) {
	_toSpawn.clear();

	if (_isActive) {
		_timer += dt;

		while (_timer >= _spawnInterval) {
			_timer -= _spawnInterval;

			_toSpawn.push_back(spawn());
		}
	}
	return _toSpawn;
}

std::vector<Particle*> ParticleGenerator::burst(int n) {
	_toSpawn.clear();
	for (int i = 0; i < n; i++) {
		_toSpawn.push_back(spawn());
	}

	return _toSpawn;
}

Particle* ParticleGenerator::spawn() {

	Particle* p = new Particle();

	p->position = physx::PxTransform(generateSpawnPosition());

	Vector3D dir = generateVelocity(p->position.p);
	
	p->radius = generateSize();
	p->color = _config.color;
	p->iniColor = _config.color;
	p->finColor = _config.finColor;
	
	p->realSpeed = generateNormal(_config.meanSpeed * _config.realToSimSpeedRatio, _config.devSpeed * _config.realToSimSpeedRatio);
	p->simulatedSpeed = generateNormal(_config.meanSpeed, _config.devSpeed);
	
	p->realMass = _config.realMass;

	p->realGravity = _config.realGravity;

	p->damping = _config.damping;
	
	p->age = 0.0;
	p->alive = true;
	p->lifetime = _config.meanLifetime;


	p->calculateSimulatedValues();

	p->velocity = dir * p->simulatedSpeed;

	p->createRenderItem();

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

Vector3D ParticleGenerator::generateVelocity(Vector3D pos) {
	switch (_config.spawnShape) {
	
		// particle moves in direction specified
	default:
	case GeneratorShape::LINE:
		return _config.meanVelocity.normalized();

	case GeneratorShape::CONE: {
		Vector3D axis = _config.meanVelocity.normalized();

		float ejectionAngleRad = _config.ejectionAngle * std::numbers::pi_v<float> / 180.0f;

		// random angle
		float cosAngle = generateUniform(std::cos(ejectionAngleRad), 1);
		float sinAngle = std::sqrt(1 - cosAngle * cosAngle);

		// random angle from central axis
		float randomAngle = generateUniform(0, 2.f * std::numbers::pi_v<float>);

		// we can use any axis as our helper, but the cross product of two parallel vectors is 0
		// so we pick y, for example, as our helper, and use it if its not nearly parallel to the axis given
		Vector3D helper = std::abs(axis.y()) > 0.999f ? Vector3D{ 1, 0, 0 } : Vector3D{ 0, 1, 0 };

		// we create a coordinate system around our axis
		// axis points straight down the cone
		// tangent and bitangent are perpendicular to the axis, point sideways
		Vector3D tangent = helper.cross(axis).normalized();
		Vector3D bitangent = axis.cross(tangent).normalized();

		// the formula would be
		// z = cos(angle from center of cone) -- we can name it z axis
		// x = cos(angle from x axis (tangent)) * sin(angle from center of cone)
		// y = sin(angle from y axis (bitangent)) * sin(angle from center of cone)
		// since bitangent, axis, and tangent all represent the x y z axes, we multiply by this coordinate system
		Vector3D finalDir = axis * cosAngle +
			tangent * (sinAngle * std::cos(randomAngle)) +
			bitangent * (sinAngle * std::sin(randomAngle));
	
		return finalDir.normalized();
	}
	case GeneratorShape::RADIAL: {
		if (_config.originShape == GeneratorOrigin::POINT) {

		}
		else {
			Vector3D finalD = pos - _config.originPoint;
			return finalD.normalized();
		}
	}
	}
	
}

float ParticleGenerator::generateSize() {
	switch (_config.sizeType) {
	case ParticleSizeType::FIXED:
	default:
		return _config.meanParticleRadius;

	case ParticleSizeType::VARIABLE:
		return generateNormal(_config.meanParticleRadius, _config.devParticleRadius);
	}
}

float ParticleGenerator::generateUniform(float min, float max) {
	return _uniformDist(_mt, std::uniform_real_distribution<float>::param_type(min, max));
}

float ParticleGenerator::generateNormal(float mean, float stddev) {
	return _normalDist(_mt, std::normal_distribution<float>::param_type(mean, stddev));
}