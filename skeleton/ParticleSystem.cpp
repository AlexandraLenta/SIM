#include "ParticleSystem.h"
#include "Particle.h"
#include "ParticleGenerator.h"

ParticleSystem::ParticleSystem(Vector3D pos, Particle config) : _particleConfig(config) {
	_particles.reserve(MAX_PARTICLES);
}

//void ParticleSystem::addGenerator(ParticleGenerator g) {
//	//_gen = g;
//}

// SO! the way this is going to work. particle system can hold many generators
// it updates those generators and passes dt
// the generators generate particles and return them to the system, which stores them in a vector and upadtse them an decides their death time and stuff and takes care of the pooling
// so there is going to be a general generator/emitter...
// and either give it a type orrr do inheritance