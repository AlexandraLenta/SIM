#pragma once
#include "ForceGenerator.h"
class BuoyancyGenerator :
    public ForceGenerator
{
public:
    BuoyancyGenerator(float liquidHalfHeight, float d, float width = 100, Vector3D pos = { 0, 0, 0 });

    void applyForceToParticle(Particle* p, double t) override;

    ~BuoyancyGenerator();

protected:
    float _height;
    float _volume;
    float _liquidDensity;
    float _gravity = 9.8;

    Particle* _liquidParticle;

};

