#pragma once
#include "Particle.h"
class Projectile :
    public Particle
{
public:
    Projectile(Vector3D pos = { 0, 0, 0 }, Vector3D vel = { 0, 0, 0 }, Vector3D a = { 0, 0, 0 }, float mR = 5, float d = 1);
    void changeRealMass(float amount);

private:
    float _realMass;
    float _simulatedMass;
    
    float _realSpeed;
    float _simulatedSpeed;

    float _realGravity;
    float _simulatedGravity;

    void calculateSimulatedValues();
};

