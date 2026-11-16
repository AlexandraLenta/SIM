#include "P4_Scene.h"

#include "RenderUtils.hpp"
#include "Vector3D.h"

P4_Scene::P4_Scene(std::string name) : Scene(std::move(name)) {}

void P4_Scene::init() {
	//createAxes();
	
	_particleSys = new ParticleSystem();

	//createAnchoredSpringDemo();
	//createSpringDemo();
	createFloatDemo();
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
	_anchoredSpringGen = static_cast<AnchoredSpringForceGenerator*>(_particleSys->addForceGenerator(std::move(std::unique_ptr<AnchoredSpringForceGenerator>(new AnchoredSpringForceGenerator(50, 10, {0, 17, 0}, p)))));
	_anchoredSpringGen->setActive(false);
}

void P4_Scene::createSpringDemo() {
	// FIRST PARTICLE -------------------------
	Particle* p1 = _particleSys->spawn();

	p1->position = physx::PxTransform(Vector3D{ -10, 0, 0 });
	p1->radius = 1;
	p1->color = { 1, 0, 0, 1 };
	p1->realGravity = 0;
	p1->simulatedSpeed = 10;
	p1->realSpeed = 50;

	p1->lifetime = 0;
	p1->damping = 0.9; // damping mas bajo para que la particula no vuele mucho cuando reactivamos el generador y esta muy lejos

	p1->calculateSimulatedValues();
	p1->createRenderItem();

	// SECOND PARTICLE -------------------------
	Particle* p2 = _particleSys->spawn();

	p2->position = physx::PxTransform(Vector3D{ 10, 0, 0 });
	p2->radius = 1;
	p2->color = { 0, 1, 0, 1 };
	p2->realGravity = 0;
	p2->simulatedSpeed = 10;
	p2->realSpeed = 50;

	p2->lifetime = 0;
	p2->damping = 0.9; // damping mas bajo para que la particula no vuele mucho cuando reactivamos el generador y esta muy lejos

	p2->calculateSimulatedValues();
	p2->createRenderItem();

	// GENERATOR ---------------------------------
	_springGen = static_cast<ElasticForceGenerator*>(_particleSys->addForceGenerator(std::move(std::unique_ptr<ElasticForceGenerator>(new ElasticForceGenerator(50, 10, p1, p2)))));
	_springGen->setActive(true);
}

void P4_Scene::createFloatDemo()
{
	_floatingParticle = _particleSys->spawn();
	_floatingParticle->cubeExtents = { 1, 1, 1 };
	_floatingParticle->shapeType = ParticleShape::Box;
	_floatingParticle->color = { 1, 0, 0, 1 };
	_floatingParticle->position = physx::PxTransform({ 0, 3, 0 });
	_floatingParticle->realGravity = -9.8;
	_floatingParticle->simulatedSpeed = 10;
	_floatingParticle->realSpeed = 50;
	_floatingParticle->realMass = 500 * 2 * 2 * 2;

	_floatingParticle->lifetime = 0;
	_floatingParticle->damping = 0.9; // damping mas bajo para que la particula no vuele mucho cuando reactivamos el generador y esta muy lejos

	_floatingParticle->calculateSimulatedValues();
	_floatingParticle->rebuildRenderItem();

	_buoyancyGen = static_cast<BuoyancyGenerator*>(_particleSys->addForceGenerator(std::move(std::unique_ptr<BuoyancyGenerator>(new BuoyancyGenerator(2, 1000)))));
	_buoyancyGen->setActive(true);
}

void P4_Scene::update(double dt) {
	if (_particleSys)
		_particleSys->update(dt);
}

void P4_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (_anchoredSpringGen) {
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
	if (_buoyancyGen) {
		if (key == 'i' || key == 'I') {
			_floatingParticle->realMass = std::max<float>((_floatingParticle->realMass / 8.f - 100) * 8.f, 0);
			_floatingParticle->calculateSimulatedValues();
			std::cout << "Decreased real mass: " << _floatingParticle->realMass << '\n';
		}
		else if (key == 'o' || key == 'O') {
			_floatingParticle->realMass = (_floatingParticle->realMass / 8.f + 100) * 8.f;
			_floatingParticle->calculateSimulatedValues();
			std::cout << "Increased real mass: " << _floatingParticle->realMass << '\n';
		}
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

	if (_springGen) {
		delete _springGen;
		_springGen = nullptr;
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