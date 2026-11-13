#include "P4_Scene.h"

#include "RenderUtils.hpp"
#include "Vector3D.h"

P4_Scene::P4_Scene(std::string name) : Scene(std::move(name)) {}

void P4_Scene::init() {
	//createAxes();
	
	_particleSys = new ParticleSystem();

	createAnchoredSpringDemo();
}

void P4_Scene::createAnchoredSpringDemo() {
	// ANCHOR -------------------
	_transforms.push_back(physx::PxTransform(Vector3D{ 0, 20, 0 }));

	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(3, 3, 3));

	_items.push_back(new RenderItem(shape, &_transforms.back(), Vector4(1, 1, 1, 1)));

	shape->release();

	// PARTICLE -------------------------
	Particle* p = _particleSys->spawn();

	p->position = physx::PxTransform(Vector3D{ 0, 0, 0});
	p->radius = 1;
	p->color = { 1, 0, 0, 1 };
	p->simulatedGravity = 20;
	p->simulatedSpeed = 10;
	p->realSpeed = 50;

	p->lifetime = 0;
	p->damping = 0.95; // damping mas bajo para que la particula no vuele mucho cuando reactivamos el generador y esta muy lejos

	p->calculateSimulatedValues();
	p->createRenderItem();

	// GENERATOR ---------------------------------
	_anchoredSpringGen = static_cast<AnchoredSpringForceGenerator*>(_particleSys->addForceGenerator(std::move(std::unique_ptr<AnchoredSpringForceGenerator>(new AnchoredSpringForceGenerator(50, 10, {0, 17, 0})))));
	_anchoredSpringGen->setActive(false);
}

void P4_Scene::update(double dt) {
	_particleSys->update(dt);
}

void P4_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'f' || key == 'F') {
		_anchoredSpringGen->setActive(!_anchoredSpringGen->getActive());
		if (_anchoredSpringGen->getActive()) {
			std::cout << "Activated anchored spring.\n";
		}
		else {
			std::cout << "Deactivated anchored spring.\n";
		}
	}
	else if (key == 'i' || key == 'I') {
		_anchoredSpringGen->setK(_anchoredSpringGen->getK() - 1);
		std::cout << "Decreased K: " << _anchoredSpringGen->getK() << '\n';
	}
	else if (key == 'o' || key == 'O') {
		_anchoredSpringGen->setK(_anchoredSpringGen->getK() + 1);
		std::cout << "Increased K: " << _anchoredSpringGen->getK() << '\n';
	}
}

void P4_Scene::cleanup() {
	for (auto* item : _items) {
		item->release();
	}
	_items.clear();
	_transforms.clear();

	if (_particleSys) {
		delete _particleSys;
		_particleSys = nullptr;
	}

	if (_anchoredSpringGen) {
		delete _anchoredSpringGen;
		_anchoredSpringGen = nullptr;
	}
}

void P4_Scene::createAxes() {
	Vector3D u = { 3, 0, 0 };
	Vector3D v = { 0, 4, 0 };

	Vector3D w = Vector3D::cross(u, v);

	u = u.normalized() * 5;
	v = v.normalized() * 5;
	w = w.normalized() * 5;

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_transforms.push_back(physx::PxTransform(u));
	_transforms.push_back(physx::PxTransform(v));
	_transforms.push_back(physx::PxTransform(w));

	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));
	_items.push_back(new RenderItem(shape, &_transforms[1], Vector4(1, 0, 0, 1)));
	_items.push_back(new RenderItem(shape, &_transforms[2], Vector4(0, 1, 0, 1)));
	_items.push_back(new RenderItem(shape, &_transforms[3], Vector4(0, 0, 1, 1)));

	shape->release();
}