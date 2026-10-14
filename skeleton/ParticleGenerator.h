#pragma once
#include "Particle.h"
#include <vector>
#include <random>

enum class GeneratorOrigin {
	POINT,
	LINE,
	INSIDE_SPHERE,
	SURFACE_SPHERE,
	BOX
};

enum class GeneratorShape {
	LINE,
	CONE
};

enum class ParticleSizeType {
	FIXED,
	VARIABLE
};

struct ParticleGenConfig {
	GeneratorOrigin originShape = GeneratorOrigin::POINT; // for position
	GeneratorShape spawnShape = GeneratorShape::CONE; // for velocity
	
	Vector3D axis = { 1, 0, 0 }; // for GeneratorOrigin::LINE
	float shapeRadius = 10; // for all GeneratorOrigin types

	Vector3D boxHalfExtents = { 10, 10, 10 }; // distance from origin to box face in the 3 axes (considering origin = 0)

	Vector3D meanVelocity = { 0, -1, 0 }; // the mean velocity direction for all GeneratorShape types


	float ejectionAngle; // for GeneratorShape::CONE

	Vector3D originPoint; // marks the origin point, center of box, center of sphere, or center of line to spawn around
	
	float meanParticleRadius; // the mean radius of the particle
};

class ParticleGenerator {
public:
	

	ParticleGenerator(ParticleGenConfig config);

	// update timer & generate particles if necessary
	std::vector<Particle*> updateGenerate(double dt);

	// spawn particle, each generator with its own configurations
	Particle* spawn();

	void setActive(bool a);
	bool isActive();

private:
	ParticleGenConfig _config;
	
	bool _isActive = true;

	// spawn particles every x seconds
	double _spawnInterval = 0.1;
	double _timer = 0.0;

	std::uniform_real_distribution<float> _uniformDist{ -1, 1 };
	std::normal_distribution<float> _normalDist{ 0, 1 };
	std::mt19937 _mt;

	Vector3D generateSpawnPosition();
	Vector3D generateVelocity();

	float generateUniform(float min, float max);
	float generateNormal(float mean, float stddev);
};