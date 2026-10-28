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

    bool isInsideVolume(Vector3D pos);
};

class TornadoGenerator :
    public WindGenerator {

public:
    /// <summary>
    /// Constructs the tornado generator with the given values.
    /// </summary>
    /// <param name="k">The strength of the tornado.</param>
    /// <param name="centerPos">The position of the tornado in at its base.</param>
    /// <param name="volume">The volume of the tornado.
    ///     _______
    ///    |       |
    ///    |       | y = tornado height
    ///    |       | 
    ///     ---.--- <-- x & z = half width
    ///     center
    ///     (x, y)
    /// </param>
    TornadoGenerator(float k, Vector3D centerPos, Vector3D volume);
    
    void applyForceToParticle(Particle* p, double t) override;
};