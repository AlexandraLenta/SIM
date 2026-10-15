#pragma once
#include "Scene.h"
#include <vector>
#include "RenderUtils.hpp"
#include <deque>

class ParticleSystem;

class P2_Scene :
    public Scene
{
public:
    explicit P2_Scene(std::string name);

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
    void cleanup() override;

private:
    std::deque<physx::PxTransform> _transforms;
    std::vector<RenderItem*> _items;

    ParticleSystem* _particleSystem;

    void createAxes();
    void createFirstGen();
    void createSecondGen();
    void createThirdGen();
};