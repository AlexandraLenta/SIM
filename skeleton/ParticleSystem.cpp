#include "ParticleSystem.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator(GeneratorShape type, Particle& config) : _shape(type), _config(config) {
	_g = NormalDistribution();
}

Particle* ParticleGenerator::spawn(Vector3D startingPos) {
	Particle* p = new Particle(_config);

	
	
	//switch (_shape) {
	//	case GeneratorShape::POINT
	//}

	return p;
}

ParticleSystem::ParticleSystem(Vector3D pos, Particle config) : _particleConfig(config), _gen(ParticleGenerator::GeneratorShape::POINT, config) {
	for (size_t i = 0; i < INITIAL_PARTICLES; i++) {
		_particles.push_back(_gen.spawn(pos));
	}
}

void ParticleSystem::setGenerator(ParticleGenerator g) {
	//_gen = g;
}