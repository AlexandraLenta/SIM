#pragma once
#include <vector>
#include <memory>
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Projectile;

class ProjectilePool
{
public:
	ProjectilePool(int nr);

	void shoot(physx::PxTransform origin, Vector3D dir);

private:
	std::vector<std::unique_ptr<Projectile>> _pool;
	std::size_t _index;

	void incrementIndex();
};

