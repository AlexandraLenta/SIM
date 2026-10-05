#include "P1_Scene.h"

#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "ProjectilePool.h"

P1_Scene::P1_Scene(std::string name) : Scene(std::move(name)) {}

void P1_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));

	createAxes();

	_projPool = new ProjectilePool(20);
}

void P1_Scene::update(double dt) {
	_projPool->updatePool(dt);
}

void P1_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'h' || key == 'H') {
		physx::PxVec3 direction = camera.q.rotate(physx::PxVec3{ 0, 0, -1 });
		_projPool->shoot(camera, direction);
	}
}

void P1_Scene::cleanup() {
	for (auto* item : _items) {
		item->release();
	}
	_items.clear();

	delete _projPool;
	_projPool = nullptr;
}

void P1_Scene::createAxes() {
	Vector3D u = { 3, 0, 0 };
	Vector3D v = { 0, 4, 0 };

	Vector3D w = Vector3D::cross(u, v);

	u = u.normalized() * 5;
	v = v.normalized() * 5;
	w = w.normalized() * 5;

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(u));
	_transforms.push_back(physx::PxTransform(v));
	_transforms.push_back(physx::PxTransform(w));
	_items.push_back(new RenderItem(shape, &_transforms[1], Vector4(1, 0, 0, 1)));
	_items.push_back(new RenderItem(shape, &_transforms[2], Vector4(0, 1, 0, 1)));
	_items.push_back(new RenderItem(shape, &_transforms[3], Vector4(0, 0, 1, 1)));
}