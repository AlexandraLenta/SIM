#pragma once
#include <vector>
#include "Vector3D.h"
#include "Projectile.h"

class ProjectilePool
{
public:
	enum class ProjectileType {
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER,
		NUM
	};

	static const float PROJECTILE_SURVIVE_TIME; // cuanto se queda el objeto en la escena desde que ha sido shot
	ProjectilePool(int nr);
	~ProjectilePool();

	void shoot(physx::PxTransform origin, Vector3D dir);
	void updatePool(float t);

	void changeSpeed(float sp);
	float getSpeed();

	void changeType();
	std::string getType();

private:
	std::vector<std::pair<Projectile*, float>> _pool;
	std::size_t _index;
	std::size_t _count;
	float _speed;

	std::vector<Projectile*> _types;
	ProjectileType _currType = ProjectileType::PISTOL;

	void incrementIndex();
};

