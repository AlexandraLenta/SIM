#pragma once
#include "Scene.h"
#include <vector>
#include <queue>

class RenderItem;
class Vector3D;
class Particle;

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

    void createAxes();
};

