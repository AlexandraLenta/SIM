#pragma once
#include "Scene.h"
#include <vector>

class RenderItem;

class P0_Scene :
    public Scene
{
public:
    explicit P0_Scene(std::string name);

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
    void cleanup() override;

private:
    std::vector<physx::PxTransform> _transforms;
    std::vector<RenderItem*> _items;

    void createAxes();
};

