#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator :
    public ForceGenerator
{
public:
    ExplosionGenerator(Vector3D center, float r, float tCt, float k);
    void applyForceToParticle(Particle* p, double t) override;

private:
    Vector3D _center;
    float _radius;
    float _timeConstant;
    float _intensity;

    bool isInsideVolume();
};