#include "P0_Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"

P0_Scene::P0_Scene(std::string name) : Scene(std::move(name)) {}

void P0_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));
}

void P0_Scene::update(double dt) {

}

void P0_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {

}

void P0_Scene::cleanup() {
	for (auto it = _items.begin(); it != _items.end(); it++) {
		(*it)->release();
		_items.erase(it);
	}
}