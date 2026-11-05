#include "Demo_Scene.h"
#include "GunManager.h"

Demo_Scene::Demo_Scene(std::string name) : Scene(std::move(name)) {}

void Demo_Scene::init() {
	_particleSys = std::unique_ptr<ParticleSystem>(new ParticleSystem());
	_gunManager = new GunManager({3, 3, 8});

	BulletConfig b1;
	b1.color = { 1, 0, 0, 1 };
	b1.iniColor = { 1, 0, 0, 1 };
	b1.finColor = { 1, 0, 0, 1 };

	_gunManager->addBulletConfig(b1);

	// TODO:
	// - wasd and camera
}

void Demo_Scene::update(double dt) {
	_gunManager->update(dt);

	_particleSys->update(dt);
}

void Demo_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'x' || key == 'X') {
		_gunManager->spawnParticle(*_particleSys);
	}
}

void Demo_Scene::cleanup() {
	if (_gunManager != nullptr) {
		delete _gunManager;
		_gunManager = nullptr;
	}
}