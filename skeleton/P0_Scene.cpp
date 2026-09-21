#include "P0_Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"


P0_Scene::P0_Scene(std::string name) : Scene(std::move(name)) {}

void P0_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));

	createAxes();

	testVisualField();
}

void P0_Scene::update(double dt) {

}

void P0_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {

}

void P0_Scene::cleanup() {
	for (auto* item : _items) {
		item->release();
	}
	_items.clear();
}

void P0_Scene::createAxes() {
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

void P0_Scene::testVisualField() {
	Vector3D enemyDir = { 0, 0, 1 };
	std::vector<Vector3D> positions = { {2, 0, 3}, { -4, 0, 1 }, { 0, 0 , -5}, { 3, 0, 0} };

	Vector4 green = { 0, 1, 0, 1 };
	Vector4 red = { 1, 0, 0, 1 };
	Vector4 yellow = { 1, 1, 0, 1 };

	for (auto pos : positions) {
		if (Vector3D::dot(enemyDir, pos) == 0) {
			createSphere(pos, yellow);
		}

		else if (Vector3D::dot(enemyDir, pos) < 0) {
			createSphere(pos, red);
		}

		else if (Vector3D::dot(enemyDir, pos) > 0) {
			createSphere(pos, green);
		}
	}
}

void P0_Scene::createSphere(Vector3D const& pos, physx::PxVec4 color) {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));

	_transforms.push_back(physx::PxTransform(pos));
	_items.push_back(new RenderItem(shape, &_transforms[(_transforms.size() - 1)], color));
}