#include "P2_Scene.h"
#include "ParticleSystem.h"

P2_Scene::P2_Scene(std::string name) : Scene(std::move(name)) {}

void P2_Scene::init() {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

	_transforms.push_back(physx::PxTransform(Vector3D(0, 0, 0)));
	_items.push_back(new RenderItem(shape, &_transforms[0], Vector4(1, 1, 1, 1)));
	createAxes();

	_particleSystem = new ParticleSystem();

	ParticleGenConfig config1 = {
		GeneratorOrigin::POINT,
		GeneratorShape::CONE,
		ParticleSizeType::VARIABLE,
	};
	
	config1.meanVelocity = { 0, 1, 0 };
	config1.meanSpeed = 35;
	config1.devSpeed = 0.2;

	config1.realToSimSpeedRatio = 10; // real speed is 10x higher than sim speed

	config1.meanLifetime = 8; // seconds

	config1.ejectionAngle = 30; // in degrees

	config1.originPoint = { 0,0,0 }; // spawn from center

	config1.meanParticleRadius = 0.5;
	config1.devParticleRadius = 0.1;
	config1.color = { 0, 0, 1, 1 };
	config1.finColor = { 1, 0, 0, 1 };

	config1.realMass = 2;
	config1.realGravity = 0; // no gravity

	config1.damping = 0.99; // minimal damping

	ParticleGenerator* gen1 = new ParticleGenerator(config1);

	_particleSystem->addGenerator(gen1);

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