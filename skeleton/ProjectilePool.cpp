#include "ProjectilePool.h"
#include "Projectile.h"
#include <algorithm>

ProjectilePool::ProjectilePool(int nr) : _index(0) {
	_pool.reserve(nr);
	for (int i = 0; i < nr; i++) {
		_pool.emplace_back(std::make_unique<Projectile>()); // populate pool
	}
}

void ProjectilePool::shoot(physx::PxTransform origin, Vector3D dir) {
	_pool[_index]->shoot(origin, dir);
}

void ProjectilePool::incrementIndex() {
	if (!_pool.empty())
		_index = std::clamp(_index, std::size_t{ 0 }, _pool.size() - 1);
}