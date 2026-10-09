#pragma once
#include "Particle.h"
class Projectile :
    public Particle
{
public:
    Projectile(Vector3D pos = { 0, 0, 0 }, float mR = 5, float sR = 30, float sS = 25, float d = 1);
    ~Projectile();
    void changeRealSpeed(float amount);
    void shoot(physx::PxTransform origin, Vector3D dir);

};

