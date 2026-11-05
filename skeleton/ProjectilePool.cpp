#include "ProjectilePool.h"
#include <algorithm>

ProjectilePool::ProjectilePool(int nr) : _index(0), _count(nr), _currType((ProjectileType)0) {
	_types.reserve((int)ProjectileType::NUM);

	Projectile* pPistol = new Projectile();
	pPistol->radius = 0.3f;
	pPistol->color = pPistol->iniColor = pPistol->finColor = Vector4(1.0f, 0.9f, 0.2f, 1.0f);
	pPistol->velocity = { 0, 0, 1 };
	pPistol->acceleration = { 0, 0, 0 };
	pPistol->simulatedSpeed = 35;
	pPistol->realSpeed = 250;
	pPistol->realMass = 0.005f;
	pPistol->realGravity = -9.81f;
	pPistol->damping = 0.99f;
	pPistol->calculateSimulatedValues();

	Projectile* pArtillery = new Projectile();
	pArtillery->radius = 0.8f;
	pArtillery->color = pArtillery->iniColor = pArtillery->finColor = Vector4(0.4f, 0.4f, 0.4f, 1.0f);
	pArtillery->velocity = { 0, 3, 4 };
	pArtillery->acceleration = { 0, 0, 0 };
	pArtillery->simulatedSpeed = 50;
	pArtillery->realSpeed = 500;
	pArtillery->realMass = 50;
	pArtillery->realGravity = -20;
	pArtillery->damping = 0.99f;
	pArtillery->calculateSimulatedValues();

	Projectile* pFireball = new Projectile();
	pFireball->radius = 0.6f;
	pFireball->color = pFireball->iniColor = Vector4(1.0f, 0.5f, 0.0f, 1.0f);
	pFireball->finColor = Vector4(1.0f, 0.1f, 0.0f, 1.0f);
	pFireball->velocity = { 0, 0, 1 };
	pFireball->acceleration = { 0, 0.6f, 0 };  
	pFireball->simulatedSpeed = 5;
	pFireball->realSpeed = 100;
	pFireball->realMass = 1;
	pFireball->realGravity = 0;
	pFireball->damping = 0.9f;
	pFireball->calculateSimulatedValues();

	Projectile* pLaser = new Projectile();
	pLaser->radius = 0.15f;
	pLaser->color = pLaser->iniColor = pLaser->finColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	pLaser->velocity = { 0, 0, 1 };
	pLaser->acceleration = { 0, 0, 0 };
	pLaser->simulatedSpeed = 100;
	pLaser->realSpeed = 900;
	pLaser->realMass = 0.001f;
	pLaser->realGravity = 0;
	pLaser->damping = 0.99f;
	pLaser->calculateSimulatedValues();

	_types.push_back(pPistol);
	_types.push_back(pArtillery);
	_types.push_back(pFireball);
	_types.push_back(pLaser);

	_speed = _types[(int)_currType]->realSpeed;
}

ProjectilePool::~ProjectilePool() {
	for (auto& p : _pool) delete p.first;
	_pool.clear();

	for (auto* t : _types) delete t;
	_types.clear();
}

void ProjectilePool::shoot(physx::PxTransform origin, Vector3D dir) {
	Projectile* p = new Projectile(*_types[(int)_currType]);
	p->realSpeed = _speed;
	p->calculateSimulatedValues();

	if (_pool.size() < (size_t)_count) {
		_pool.emplace_back(p, 0.0f);
		_index = _pool.size() - 1;
	}
	else {
		incrementIndex();
		delete _pool[_index].first;
		_pool[_index].first = p;
		_pool[_index].second = 0.0f;
	}

	p->shoot(origin, dir);
}

void ProjectilePool::incrementIndex() {
	if (!_pool.empty())
		_index = (_index + 1) % _pool.size();
}

void ProjectilePool::updatePool(float t) {
	for (auto it = _pool.begin(); it != _pool.end();) {
		it->second += t;
		if (it->second >= PROJECTILE_SURVIVE_TIME) {
			delete it->first;
			it = _pool.erase(it);
		}
		else {
			it->first->integrateEulerSemiImplicit(t);
			++it;
		}
	}
 
	if (_index >= _pool.size()) _index = 0;
}

void ProjectilePool::changeSpeed(float s) {
	_speed = (((_speed + s) > (10.0f)) ? (_speed + s) : (10.0f));

	// keep projectiles already in flight consistent with the new value
	for (auto& p : _pool) {
		p.first->realSpeed = _speed;
		p.first->calculateSimulatedValues();
	}
}

float ProjectilePool::getSpeed() {
	return _speed;
}

void ProjectilePool::changeType() {
	_currType = (ProjectileType)(((int)_currType + 1) % (int)ProjectileType::NUM);
	_speed = _types[(int)_currType]->realSpeed;
}

std::string ProjectilePool::getType() {
	switch (_currType) {
	case ProjectileType::PISTOL:
		return "Pistol";
		break;
	case ProjectileType::ARTILLERY:
		return "Artillery";
		break;
	case ProjectileType::FIREBALL:
		return "Fireball";
		break;
	case ProjectileType::LASER:
		return "Laser";
		break;
	}
}

const float ProjectilePool::PROJECTILE_SURVIVE_TIME = 8.0f;