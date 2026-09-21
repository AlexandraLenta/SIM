#pragma once
#include "Scene.h"
#include <vector>
#include <queue>

class RenderItem;
class Vector3D;

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
    std::deque<physx::PxTransform> _transforms;
    std::vector<RenderItem*> _items;

    void createAxes();
    void testVisualField();
    void createSphere(const Vector3D& pos, physx::PxVec4 color, float size);
    void testLerp();
};

