#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include <vector>

class ParticleGenerator {
public:
	//enum class GeneratorShape {
	//	POINT,
	//	CONE,
	//	SQUARE
	//};

	ParticleGenerator(Particle& config);

	// update timer & generate particles if necessary
	std::vector<Particle*> update(double dt);

	// spawn particle, each generator with its own configurations
	virtual Particle* spawn() = 0;

	void setActive(bool a);
	bool isActive();

private:
	Particle& _config;
	
	bool _isActive = true;
	double _spawnInterval = 0.1;
	double _timer = 0.0;
	
};