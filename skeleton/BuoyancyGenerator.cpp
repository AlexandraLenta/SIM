#include "BuoyancyGenerator.h"

BuoyancyGenerator::BuoyancyGenerator(float liquidHalfHeight, float d, float width, Vector3D pos)
    : ForceGenerator(), _height(liquidHalfHeight), _liquidDensity(d) {
    _liquidParticle = new Particle({ width, liquidHalfHeight, width }, { 0, 0, 1, 1 });
    _liquidParticle->position = physx::PxTransform(pos);
    _liquidParticle->velocity = { 0, 0, 0 };
    _liquidParticle->realGravity = 0;
}

BuoyancyGenerator::~BuoyancyGenerator() {
	if (_liquidParticle) {
		delete _liquidParticle; _liquidParticle = nullptr;
	}
}

void BuoyancyGenerator::applyForceToParticle(Particle* p, double t) {
    float h = p->position.p.y;
    float h0 = _liquidParticle->position.p.y + _height;      // surface = top of liquid box

    float objHeight = 2.0f * p->cubeExtents.y();                // half-extents -> full height
    float objVolume = 8.0f * p->cubeExtents.x() * p->cubeExtents.y() * p->cubeExtents.z();

    float immersed;

    if (h - h0 > objHeight * 0.5f)       
        immersed = 0.0f;
    else if (h0 - h > objHeight * 0.5f)  
        immersed = 1.0f;
    else
        immersed = (h0 - h) / objHeight + 0.5f;

    float g = std::abs(p->realGravity);

    Vector3D force(0, _liquidDensity * objVolume * immersed * g, 0);

    p->applyForce(force);
}