#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator :
    public ForceGenerator
{
public:
    SpringForceGenerator(double k, double restL, Particle* other);

    void applyForceToParticle(Particle* p, double t) override;

    void setK(double k);

protected:
    double _k;
    double _restingLength;
    Particle* _otherParticle;
};

class AnchoredSpringForceGenerator : 
    public SpringForceGenerator 
{
public:
    AnchoredSpringForceGenerator(double k, double restL, const Vector3D& anchorPos);
    ~AnchoredSpringForceGenerator();
};