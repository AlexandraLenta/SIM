#include "P2_Scene.h"
#include "ParticleSystem.h"

P2_Scene::P2_Scene(std::string name) : Scene(std::move(name)) {}

void P2_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));
	createAxes();

	_particleSystem = new ParticleSystem();

	createFirstGen();
	createSecondGen();
	createThirdGen();
}

void P2_Scene::cleanup() {
	delete _particleSystem;
	_particleSystem = nullptr;

	for (auto* item : _items) {
		item->release();
	}
	_items.clear();
}

void P2_Scene::update(double dt) {
	_particleSystem->update(dt);
}

void P2_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'v' || key == 'V')
		_particleSystem->burst(20, 2);
}

void P2_Scene::createAxes() {
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

void P2_Scene::createFirstGen() {
	ParticleGenConfig config1 = {
		GeneratorOrigin::POINT,
		GeneratorShape::CONE,
		ParticleSizeType::VARIABLE,
	};

	config1.meanVelocity = { 0, 1, 0 };
	config1.meanSpeed = 20;
	config1.devSpeed = 0.2;

	config1.meanLifetime = 5; // seconds

	config1.ejectionAngle = 20; // in degrees

	config1.originPoint = { -20,0,0 }; // spawn from center

	config1.meanParticleRadius = 0.5;
	config1.devParticleRadius = 0.1;
	config1.color = { 0, 0, 1, 1 };
	config1.finColor = { 1, 0, 0, 1 };

	config1.realMass = 2;
	config1.realGravity = -20; 

	config1.damping = 0.99; // minimal damping

	ParticleGenerator* gen1 = new ParticleGenerator(config1);

	_particleSystem->addGenerator(gen1);

}

void P2_Scene::createSecondGen() {
	ParticleGenConfig config2 = {
		GeneratorOrigin::BOX,
		GeneratorShape::LINE,
		ParticleSizeType::FIXED,
	};

	config2.boxHalfExtents = { 10, 1, 10 }; // not that tall

	config2.meanVelocity = { 0, -1, 0 }; // fall down like rain
	config2.meanSpeed = 25;
	config2.devSpeed = 0.2;

	config2.realToSimSpeedRatio = 10; // real speed is 10x higher than sim speed

	config2.meanLifetime = 10; // seconds

	config2.originPoint = { 0, 50, 0 }; // higher up

	config2.meanParticleRadius = 0.3;

	config2.color = { 0, 0, 1, 1 };
	config2.finColor = { 0, 1, 0, 1 };

	config2.realMass = 1;
	config2.realGravity = -9.81; // normal gravity

	config2.damping = 0.9; // minimal damping

	ParticleGenerator* gen2 = new ParticleGenerator(config2);
	gen2->setSpawnInterval(0.2);

	_particleSystem->addGenerator(gen2);

}

void P2_Scene::createThirdGen() {
	ParticleGenConfig config3 = {
		GeneratorOrigin::SURFACE_SPHERE,
		GeneratorShape::RADIAL,
		ParticleSizeType::FIXED,
	};

	config3.shapeRadius = 8;

	config3.meanVelocity = { 0, -1, 0 }; // fall down like rain
	config3.meanSpeed = 25;
	config3.devSpeed = 0.2;

	config3.realToSimSpeedRatio = 10; // real speed is 10x higher than sim speed

	config3.meanLifetime = 5; // seconds

	config3.originPoint = { 20, 0, 0 }; // higher up

	config3.meanParticleRadius = 0.3;

	config3.color = { 0, 0, 1, 1 };
	config3.finColor = { 0, 0, 1, 1 };

	config3.realMass = 1;
	config3.realGravity = 0; // normal gravity

	config3.damping = 0.9; // minimal damping

	ParticleGenerator* gen3 = new ParticleGenerator(config3);
	gen3->setSpawnInterval(0.4);

	_particleSystem->addGenerator(gen3);

}