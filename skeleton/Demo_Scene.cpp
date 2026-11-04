#include "Demo_Scene.h"
#include "GunManager.h"

Demo_Scene::Demo_Scene(std::string name) : Scene(std::move(name)) {}

void Demo_Scene::init() {
	_gun.first = physx::PxTransform({ 0, 0, 0 });
	_gun.second = new RenderItem(CreateShape(physx::PxBoxGeometry(1, 1, 2)), &_gun.first, Vector4(1, 1, 1, 1));

	_particleSys = std::unique_ptr<ParticleSystem>(new ParticleSystem());
	_gunManager = new GunManager();

	// TODO:
	// - move gun movement logic and visual to the gun manager class
	// - add bullet config and test shooting
	// - gun movement, wasd and camera
}

void Demo_Scene::update(double dt) {

}

void Demo_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'x' || key == 'X') {
		_gunManager->spawnParticle(*_particleSys);
	}
}

void Demo_Scene::cleanup() {
	if (_gun.second != nullptr) {
		delete _gun.second;
		_gun.second = nullptr;
	}

	if (_gunManager != nullptr) {
		delete _gunManager;
		_gunManager = nullptr;
	}
}