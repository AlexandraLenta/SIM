#pragma once
#include "Scene.h"
#include <queue>
#include "RenderUtils.hpp"
#include "SpringForceGenerator.h"
#include "ParticleSystem.h"
#include "BuoyancyGenerator.h"

class P4_Scene :
    public Scene
{
public:
    explicit P4_Scene(std::string name);

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
    void cleanup() override;

private:
    std::deque<physx::PxTransform> _transforms;
    std::vector<RenderItem*> _items;

    AnchoredSpringForceGenerator* _anchoredSpringGen = nullptr;
    ElasticForceGenerator* _springGen = nullptr;
    BuoyancyGenerator* _buoyancyGen = nullptr;

    ParticleSystem* _particleSys = nullptr;

    void createAxes();

    void createAnchoredSpringDemo();
    void createSpringDemo();
    void createFloatDemo();
};