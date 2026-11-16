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
    float h = p->position.p.y; // position of the center of the object
    float h0 = _liquidParticle->position.p.y + _height; // position of the surface of the liquid

    float objHeight = 2.0f * p->cubeExtents.y(); // cube extents is half the edge length
    float objVolume = 8.0f * p->cubeExtents.x() * p->cubeExtents.y() * p->cubeExtents.z();

    float immersed; // fraction of object submerged

    float speedRatio = p->realSpeed / p->simulatedSpeed; // for calculating simulated liquid density

    // if object is above halfway submerged
    if (h - h0 > objHeight * 0.5f)   
        immersed = 0.0f;
    else if (h0 - h > objHeight * 0.5f)  
        immersed = 1.0f;
    else
        immersed = (h0 - h) / objHeight + 0.5f;

    float g = std::abs(p->simulatedGravity);

    Vector3D force(0, _liquidDensity * objVolume * immersed * g * speedRatio * speedRatio, 0);

    p->applyForce(force);
}