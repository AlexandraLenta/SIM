#include "ProjectilePool.h"

ProjectilePool::ProjectilePool(int nr, float sp) : _index(0), _count(nr), _speed(sp) {

}

void ProjectilePool::shoot(physx::PxTransform origin, Vector3D dir) {
	if (_pool.size() < _count) {
		Projectile* p = new Projectile();
		p->setRealSpeed(_speed);
		_pool.emplace_back(p, 0); // populate pool
		_index = _pool.size() - 1;
	}
	else {
		incrementIndex();
	}
	
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

			if (_pool.empty()) {
				_index = 0;
			}
			else if (_index >= _pool.size()) {
				_index = 0;
			}
		}
		else {
			(*it).first->integrateEulerSemiImplicit(t);
			it++;
		}
		
	}
}

void ProjectilePool::changeSpeed(float s) {
	_speed += s;
	for (auto p : _pool) {
		p.first->changeRealSpeed(s);
	}
}

float ProjectilePool::getSpeed() {
	return _speed;
}

const float ProjectilePool::PROJECTILE_SURVIVE_TIME = 8.0f;