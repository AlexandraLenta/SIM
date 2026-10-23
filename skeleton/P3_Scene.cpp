#include "P3_Scene.h"
#include "Particle.h"
#include "GravityGenerator.h"

P3_Scene::P3_Scene(std::string name) : Scene(std::move(name)) {}

void P3_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));
	createAxes();

	_p1 = new Particle(2.f, {1, 0, 0, 1});
	_p1->position = { 0, 10, 0 };
	_p1->velocity = { 0, 0, 0 };
	_p1->acceleration = { 0, 0, 0 };
	_p1->realGravity = 0;
	_p1->realMass = 2;
	_p1->realSpeed = 10;
	_p1->simulatedSpeed = 5;
	_p1->lifetime = 200;
	_p1->calculateSimulatedValues();

	_p2 = new Particle(2.f, { 0, 1, 0, 1 });
	_p2->position = { 10, 10, 0 };
	_p2->velocity = { 0, 0, 0 };
	_p2->acceleration = { 0, 0, 0 };
	_p2->realGravity = 0;
	_p2->realMass = 20;
	_p2->realSpeed = 10;
	_p2->simulatedSpeed = 5;
	_p2->lifetime = 200;
	_p2->calculateSimulatedValues();


	_gen1 = new GravityGenerator({0, -9.8, 0});

	_gen2 = new GravityGenerator({ 0, -9.8, 0 });
}

void P3_Scene::cleanup() {
	delete _p1; _p1 = nullptr;
	delete _p2; _p2 = nullptr;
	delete _gen1; _gen1 = nullptr;
	delete _gen2; _gen2 = nullptr;

	for (auto* item : _items) {
		item->release();
	}
	_items.clear();
}

void P3_Scene::update(double dt) {
	_gen1->applyForceToParticle(_p1, dt);
	_gen2->applyForceToParticle(_p2, dt);

	_p1->update(dt);
	_p2->update(dt);
}

void P3_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	
}

void P3_Scene::createAxes() {
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