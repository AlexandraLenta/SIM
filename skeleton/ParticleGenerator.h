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
	CONE,
	RADIAL // TODO: implement radial 
};

enum class ParticleSizeType {
	FIXED,
	VARIABLE
};

struct ParticleGenConfig {
	GeneratorOrigin originShape = GeneratorOrigin::POINT; // for position
	GeneratorShape spawnShape = GeneratorShape::CONE; // for velocity
	ParticleSizeType sizeType = ParticleSizeType::FIXED;
	
	Vector3D axis = { 1, 0, 0 }; // for GeneratorOrigin::LINE
	float shapeRadius = 10; // for all GeneratorOrigin types

	Vector3D boxHalfExtents = { 10, 10, 10 }; // distance from origin to box face in the 3 axes (considering origin = 0)

	Vector3D meanVelocity = { 0, -1, 0 }; // the mean velocity direction for all GeneratorShape types
	float meanSpeed = 10; // mean speed of the particle
	float devSpeed = 0.2;

	float realToSimSpeedRatio = 10; // real speed is 10 times bigger than simulated speed

	float meanLifetime = 10;

	float ejectionAngle; // for GeneratorShape::CONE

	Vector3D originPoint; // marks the origin point, center of box, center of sphere, or center of line to spawn around
	
	float meanParticleRadius = 2; // the mean radius of the particle
	float devParticleRadius = 0.5;

	Vector4 color = { 1, 0, 0, 1 };
	Vector4 finColor = { 1, 0, 0, 1 };

	float realMass = 2;
	float realGravity = 0;

	float damping = 1;
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

	void setSpawnInterval(double t);

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
	float generateSize();

	float generateUniform(float min, float max);
	float generateNormal(float mean, float stddev);
};