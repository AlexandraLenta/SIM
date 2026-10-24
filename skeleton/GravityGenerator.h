#pragma once
#include "ForceGenerator.h"


class GravityGenerator :
    public ForceGenerator
{
public:
    GravityGenerator() = default;
    GravityGenerator(Vector3D gravity);

    void setGravity(Vector3D acc);

    Vector3D getGravity();

    void applyForceToParticle(Particle* p, double t) override;

private:
    Vector3D _gravity = { 0, -9.8, 0 };
};

