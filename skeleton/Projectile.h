#pragma once
#include "Particle.h"

struct Projectile :
    public Particle
{
    Projectile();
    ~Projectile();
    void changeRealSpeed(float amount);
    void shoot(physx::PxTransform origin, Vector3D dir);

};