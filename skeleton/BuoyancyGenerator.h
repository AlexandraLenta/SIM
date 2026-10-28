#pragma once
#include "ForceGenerator.h"
class BuoyancyGenerator :
    public ForceGenerator
{
public:
    BuoyancyGenerator(float h, float V, float d);

    void applyForceToParticle(Particle* p, double t) override;

    ~BuoyancyGenerator();

protected:
    float _height;
    float _volume;
    float _liquidDensity;
    float _gravity = 9.8;
    
    Particle* _liquidParticle;

};

