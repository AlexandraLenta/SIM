#pragma once
#include "Particle.h"
class Projectile :
    public Particle
{
public:
    Projectile(Vector3D pos = { 0, 0, 0 }, float mR = 5, float sR = 100, float sS = 25, float d = 1);
    ~Projectile();
    void changeRealMass(float amount);
    void integrateEulerSemiImplicit(double t) override;
    void shoot(physx::PxTransform origin, Vector3D dir);

private:
    float _realMass;
    float _simulatedMass;
    
    float _realSpeed;
    float _simulatedSpeed;

    float _realGravity;
    float _simulatedGravity;

    void calculateSimulatedValues();
};

