#include "GunManager.h"
#include "ParticleSystem.h"

GunManager::GunManager() : _configs() {

}

void GunManager::addBulletConfig(BulletConfig b) {
	_configs.push_back(b);
}

void GunManager::changeConfig() {
	_currConfigIndex = (_currConfigIndex + 1) % _configs.size();
}

void GunManager::spawnParticle(ParticleSystem& pSys) {
	Particle* p = pSys.spawn();

	BulletConfig& currConfig = _configs[_currConfigIndex];

	p->init(currConfig);

	p->applyForce(currConfig.direction.normalized() * currConfig.shotForce);
}