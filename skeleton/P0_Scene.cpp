#include "P0_Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"


P0_Scene::P0_Scene(std::string name) : Scene(std::move(name)) {}

void P0_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));

	createAxes();
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

void P0_Scene::createAxes() {
	Vector3D u = { 3, 1, 0 };
	Vector3D v = { 0, 4, 0 };

	Vector3D w = Vector3D::cross(u, v);

	std::cout << u << ' ' << v << ' ' << w << '\n';
 
	u = u.normalize() * 5;
	v = v.normalize() * 5;
	w = w.normalize() * 5;

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));

	_transforms.push_back(physx::PxTransform(u));
	_transforms.push_back(physx::PxTransform(v));
	_transforms.push_back(physx::PxTransform(w));
	_items.push_back(new RenderItem(shape, &_transforms[1], Vector4(1, 0, 0, 1)));
	_items.push_back(new RenderItem(shape, &_transforms[2], Vector4(0, 1, 0, 1)));
	_items.push_back(new RenderItem(shape, &_transforms[3], Vector4(0, 0, 1, 1)));
}