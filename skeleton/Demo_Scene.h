#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "RenderUtils.hpp"

class GunManager;

/// <summary>
/// Scene created for the presentation of the game demo.
/// Features:
///     - player can shoot from the position of the gun (represented by a cube) towards the direction of the mouse
///     - the player can change bullet types by pressing z and c
///     - the player shoots by pressing x
///     - there are 3 types of bullets: light, medium, heavy
/// </summary>
class Demo_Scene : public Scene
{
public:
    explicit Demo_Scene(std::string name);

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
    void cleanup() override;

private:
    physx::PxQuat rotationFromTo(const physx::PxVec3& from, const physx::PxVec3& to);

    GunManager* _gunManager = nullptr;
    std::unique_ptr<ParticleSystem> _particleSys = nullptr;
};