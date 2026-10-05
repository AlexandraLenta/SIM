#include "ProjectilePool.h"

ProjectilePool::ProjectilePool(int nr) : _index(0), _count(nr) {

}

void ProjectilePool::shoot(physx::PxTransform origin, Vector3D dir) {
	if (_pool.size() < _count) {
		_pool.emplace_back(new Projectile(), 0); // populate pool
	}

	incrementIndex();
	
	_pool[_index].first->shoot(origin, dir);
	_pool[_index].second = 0; // reset life time
	
}

void ProjectilePool::incrementIndex() {
	if (!_pool.empty())
		_index = (_index + 1) % _pool.size();
}

void ProjectilePool::updatePool(float t) {
	for (auto it = _pool.begin(); it != _pool.end();) {
		(*it).second += t;
		if ((*it).second >= PROJECTILE_SURVIVE_TIME) {
			delete (*it).first;
			it = _pool.erase(it);
		}
		else {
			(*it).first->integrateEulerSemiImplicit(t);
			it++;
		}
		
	}
}

const float ProjectilePool::PROJECTILE_SURVIVE_TIME = 5.0f;