#pragma once
#include "ForceGenerator.h"
class WindGenerator :
    public ForceGenerator
{
public:
    // Volume may only be rectangular.
    WindGenerator(Vector3D windVel, Vector3D volumeCenter, Vector3D volumeExtents, float k1 = 0.5, float k2 = 0);
    void applyForceToParticle(Particle* p, double t) override;

protected:
    Vector3D _velocity;
    Vector3D _center; // center of the volume
    Vector3D _extents; // distance from center to each of the rectangular sides
    float _k1;
    float _k2;

    virtual bool isInsideVolume(Vector3D pos) const;
};

class TornadoGenerator :
    public WindGenerator {

public:
    TornadoGenerator(Vector3D centerPos, Vector3D volume, float strength, float upStrength = 50, float k1 = 0.5, float k2 = 0);
    
    void applyForceToParticle(Particle* p, double t) override;

private:
    float _strength;
    float _upStrength;
};