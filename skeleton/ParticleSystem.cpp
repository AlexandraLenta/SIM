#include "ParticleSystem.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator(GeneratorShape type) : _shape(type) {
	_g = NormalDistribution();
}

Particle* ParticleGenerator::spawn(Vector3D startingPos, Vector3D dir) {
	Particle* p = new Particle();
	
	//switch (_shape) {
	//	case GeneratorShape::POINT
	//}

	return p;
}

ParticleSystem::ParticleSystem(Vector3D pos, Particle config) : _gen(ParticleGenerator::GeneratorShape::POINT) {
	for (size_t i = 0; i < INITIAL_PARTICLES; i++) {
		Particle p;
		p.position = physx::PxTransform(pos);
		//p.velocity = 
	}
}

void ParticleSystem::setGenerator(ParticleGenerator& g) {
	_gen = g;
}