#pragma once
#include "ForceGenerator.h"
class WindGenerator :
    public ForceGenerator
{
public:
    // Volume may only be rectangular.
    WindGenerator(Vector3D windVel, Vector3D volumeCenter, Vector3D volumeExtents, float k1 = 0.5, float k2 = 0);
    void applyForceToParticle(Particle* p, double t) override;

private:
    Vector3D _velocity;
    Vector3D _center;
    Vector3D _extents;
    float _k1;
    float _k2;

    bool isInsideVolume(Vector3D pos);
};