#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator :
    public ForceGenerator
{
public:
    ExplosionGenerator(Vector3D center, float r, float tCt, float k, float sV = 330);
    void applyForceToParticle(Particle* p, double t) override;

    void explode();

    void applyForce(std::vector<Particle*> p, double t) override;

private:
    Vector3D _center;
    float _radius;
    float _timeConstant;
    float _intensity;
    double _timeSinceExplosion;
    bool _active;
    float _explosionVel;
};