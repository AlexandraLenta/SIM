#include "P3_Scene.h"
#include "Particle.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"

P3_Scene::P3_Scene(std::string name) : Scene(std::move(name)) {}

void P3_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));
	createAxes();

	_particleSys = new ParticleSystem();
	
	createParticleGen();
	
	WindGenerator* gen = new WindGenerator({ 100, 0, 0 }, { 0, 0, 0 }, { 10, 10, 10 }); // blow in +x, centered on origin, size 2 in each direction from center
	TornadoGenerator* gen2 = new TornadoGenerator({ 0, 0, 0 }, { 50, 50, 50 }, 20, 10);

	_particleSys->addForceGenerator(gen2);
}

void P3_Scene::createGravityTest() {
	_p1 = new Particle(2.f, { 1, 0, 0, 1 });
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


	_gen1 = new GravityGenerator({ 0, -9.8, 0 });

	_gen2 = new GravityGenerator({ 0, -9.8, 0 });
}

void P3_Scene::createParticleGen() {
	ParticleGenConfig config1 = {
		GeneratorOrigin::POINT,
		GeneratorShape::CONE,
		ParticleSizeType::VARIABLE,
	};

	config1.meanVelocity = { 0, 1, 0 };
	config1.meanSpeed = 20;
	config1.devSpeed = 0.2;

	config1.realToSimSpeedRatio = 1; // real speed is equal to sim speed

	config1.meanLifetime = 5; // seconds

	config1.ejectionAngle = 20; // in degrees

	config1.originPoint = { 0,0,0 }; // spawn from center

	config1.meanParticleRadius = 0.5;
	config1.devParticleRadius = 0.1;
	config1.color = { 0, 0, 1, 1 };
	config1.finColor = { 1, 0, 0, 1 };

	config1.realMass = 2;
	config1.realGravity = -20;

	config1.damping = 0.99; // minimal damping

	ParticleGenerator* gen1 = new ParticleGenerator(config1);

	_particleSys->addGenerator(gen1);

}

void P3_Scene::cleanup() {
	if (_p1) {
		delete _p1; _p1 = nullptr;
	}
	if (_p2) {
		delete _p2; _p2 = nullptr;
	}
	if (_gen1) {
		delete _gen1; _gen1 = nullptr;
	}
	if (_gen2) {
		delete _gen2; _gen2 = nullptr;
	}

	for (auto* item : _items) {
		item->release();
	}
	_items.clear();

	if (_particleSys) {
		delete _particleSys; _particleSys = nullptr;
	}
}

void P3_Scene::update(double dt) {
	if (_gen1)
		_gen1->applyForceToParticle(_p1, dt);
	if (_gen2)
		_gen2->applyForceToParticle(_p2, dt);

	if (_p1)
		_p1->update(dt);
	
	if (_p2)
		_p2->update(dt);

	_particleSys->update(dt);
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