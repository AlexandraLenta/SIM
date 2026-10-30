#pragma once
#include "Scene.h"
#include <vector>
#include "RenderUtils.hpp"
#include <deque>
#include "Particle.h"
#include "GravityGenerator.h"
#include "ParticleSystem.h"
#include "ExplosionGenerator.h"

class P3_Scene :
    public Scene
{
public:
    explicit P3_Scene(std::string name);

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
    void cleanup() override;

private:
    std::deque<physx::PxTransform> _transforms;
    std::vector<RenderItem*> _items;
    std::vector<ForceGenerator*> _generators;

    ParticleSystem* _particleSys = nullptr;
    ParticleSystem* _particleSys1 = nullptr;

    Particle* _p1 = nullptr;
    Particle* _p2 = nullptr;
    GravityGenerator* _gen1 = nullptr;
    GravityGenerator* _gen2 = nullptr;

    ExplosionGenerator* _explosion = nullptr;

    void createAxes();
    void createParticleGen();
    void createGravityTest();
};