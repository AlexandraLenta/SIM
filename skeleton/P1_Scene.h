#pragma once
#include "Scene.h"
#include <vector>
#include <queue>
#include "Particle.h"

class RenderItem;
class Vector3D;

class P1_Scene :
    public Scene
{
public:
    explicit P1_Scene(std::string name);

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
    void cleanup() override;

private:
    std::deque<physx::PxTransform> _transforms;
    std::vector<RenderItem*> _items;
    //ProjectilePool* _projPool;
    Particle* p;

    void createAxes();
};