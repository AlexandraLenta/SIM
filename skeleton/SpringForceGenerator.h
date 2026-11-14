#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator :
    public ForceGenerator
{
public:
    SpringForceGenerator(double k, double restL, Particle* first, Particle* second);

    void virtual applyForce(std::vector<Particle*> p, double t) override;
    void applyForceToParticle(Particle* p, double t) override;

    void setK(double k);
    double getK();

protected:
    double _k;
    double _restingLength;
    Particle* _firstParticle;
    Particle* _secondParticle;
};

class AnchoredSpringForceGenerator : 
    public SpringForceGenerator 
{
public:
    AnchoredSpringForceGenerator(double k, double restL, const Vector3D& anchorPos, Particle* first);
    ~AnchoredSpringForceGenerator();

    void applyForceToParticle(Particle* p, double t) override;
};

class ElasticForceGenerator :
    public SpringForceGenerator {
public:
    ElasticForceGenerator(double k, double restL, Particle* first, Particle* second);

    void applyForceToParticle(Particle* p, double t) override;
};