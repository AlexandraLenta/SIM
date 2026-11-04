#include "Demo_Scene.h"

Demo_Scene::Demo_Scene(std::string name) : Scene(std::move(name)) {}

void Demo_Scene::init() {
	_gun.first = physx::PxTransform({ 0, 0, 0 });
	_gun.second = new RenderItem(CreateShape(physx::PxBoxGeometry(1, 1, 2)), &_gun.first, Vector4(1, 1, 1, 1));

	_particleSys = new ParticleSystem();
}

void Demo_Scene::update(double dt) {

}

void Demo_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	
}

void Demo_Scene::cleanup() {
	if (_gun.second != nullptr) {
		delete _gun.second;
		_gun.second = nullptr;
	}
}