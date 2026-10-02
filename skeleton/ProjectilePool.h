#pragma once
#include <vector>

class Projectile;

class ProjectilePool
{
public:
	ProjectilePool(int nr);

	void shoot();

private:
	std::vector<Projectile*> _pool;
	int _index;

	void refreshPool();
};

