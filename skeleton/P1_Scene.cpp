#include "P1_Scene.h"

#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "ProjectilePool.h"

P1_Scene::P1_Scene(std::string name) : Scene(std::move(name)) {}

void P1_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));

	createAxes();
	pPistol = new Particle(0.8, {1, 0, 0, 1});
	pPistol->position = { 0, 4, 0 };
	pPistol->velocity = { 0, 0, 1 };
	pPistol->acceleration = { 0, -1, 0 };
	pPistol->simulatedSpeed = 35;
	pPistol->realSpeed = 250;
	pPistol->realMass = 0.005;
	pPistol->realGravity = -9.81;
	pPistol->damping = 0.99;
	pPistol->calculateSimulatedValues();
	pPistol->simulatedGravity = -1;

	pArtillery = new Particle(0.8, { 0, 1, 0, 1 });
	pArtillery->position = { 0, 1, 0 };
	pArtillery->velocity = { 0, 3, 4 };
	pArtillery->acceleration = { 0, -20, 0 };
	pArtillery->simulatedSpeed = 50;
	pArtillery->realSpeed = 500;
	pArtillery->realMass = 50;
	pArtillery->realGravity = -9.81;
	pArtillery->damping = 0.99;
	pArtillery->calculateSimulatedValues();
	pPistol->simulatedGravity = -20;

	pFireball = new Particle(0.8, { 0, 0, 1, 1 });
	pFireball->position = { 0, 2, 0 };
	pFireball->velocity = { 0, 0, 1 };
	pFireball->acceleration = { 0, 0.6, 0 };
	pFireball->simulatedSpeed = 5;
	pFireball->realSpeed = 100;
	pFireball->realMass = 1;
	pFireball->realGravity = 0;
	pFireball->damping = 0.9;
	pFireball->calculateSimulatedValues();
	pPistol->simulatedGravity = 0.6;

	pLaser = new Particle(0.8, { 0, 1, 1, 1 });
	pLaser->position = { 0, 3, 0 };
	pLaser->velocity = { 0, 0, 1 };
	pLaser->acceleration = { 0, 0.6, 0 };
	pLaser->simulatedSpeed = 100;
	pLaser->realSpeed = 900;
	pLaser->realMass = 0.001;
	pLaser->realGravity = 0;
	pLaser->damping = 0.99;
	pLaser->calculateSimulatedValues();
	pPistol->simulatedGravity = 0;
}

void P1_Scene::update(double dt) {
	pPistol->integrateEulerSemiImplicit(dt);
	pArtillery->integrateEulerSemiImplicit(dt);
	pFireball->integrateEulerSemiImplicit(dt);
	pLaser->integrateEulerSemiImplicit(dt);
}

void P1_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	//if (key == 'h' || key == 'H') {
	//	physx::PxVec3 direction = camera.q.rotate(physx::PxVec3{ 0, 0, -1 });
	//	_projPool->shoot(camera, direction);
	//}
	//else if (key == 'i' || key == 'I') {
	//	_projPool->changeSpeed(-10);
	//	std::cout << "DECREASE " << _projPool->getSpeed();
	//}
	//else if (key == 'o' || key == 'O') {
	//	_projPool->changeSpeed(10);
	//	std::cout << "INCREASE " << _projPool->getSpeed();
	//}
	if (key == 'f') {
		pArtillery->changeColor({ 1, 1, 1, 1 });
		std::cout << "Changing colors\n";
	}
}

void P1_Scene::cleanup() {
	for (auto* item : _items) {
		item->release();
	}
	_items.clear();

	delete pPistol;
	pPistol = nullptr;
	delete pArtillery;
	pArtillery = nullptr;
	delete pFireball;
	pFireball = nullptr;
	delete pLaser;
	pLaser = nullptr;
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