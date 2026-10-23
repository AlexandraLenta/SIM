#pragma once
#include "Scene.h"
#include <vector>
#include "RenderUtils.hpp"
#include <deque>
#include "Particle.h"
#include "GravityGenerator.h"

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

    Particle* _p1;
    Particle* _p2;
    GravityGenerator* _gen1;
    GravityGenerator* _gen2;

    void createAxes();
};