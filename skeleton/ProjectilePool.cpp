#include "ProjectilePool.h"
#include "Projectile.h"

ProjectilePool::ProjectilePool(int nr) {
	_index = 0;
	_pool = std::vector<Projectile*>(nr, new Projectile());
}