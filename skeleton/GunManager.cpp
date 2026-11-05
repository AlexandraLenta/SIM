#include "GunManager.h"
#include "ParticleSystem.h"

physx::PxQuat lookRotation(const physx::PxVec3& forward) {
	physx::PxVec3 up(0, 1, 0);

	// if looking straight up/down, "up" is degenerate, so pick another one
	if (fabsf(forward.dot(up)) > 0.999f) up = physx::PxVec3(0, 0, 1);

	physx::PxVec3 right = up.cross(forward).getNormalized();
	physx::PxVec3 trueUp = forward.cross(right);

	return physx::PxQuat(physx::PxMat33(right, trueUp, forward));
}

GunManager::GunManager(Vector3D size) : _configs(), _size(size) {
	_gun.first = physx::PxTransform({ 0, 0, 0 });
	_gun.second = new RenderItem(CreateShape(physx::PxBoxGeometry(size.x(), size.y(), size.z())), &_gun.first, Vector4(1, 1, 1, 1));
}

GunManager::~GunManager() {
	if (_gun.second != nullptr) {
		delete _gun.second;
		_gun.second = nullptr;
	}
}

void GunManager::update(double dt) {
	physx::PxVec3 origin, rayDir;
	if (GetMouseRay(origin, rayDir)) {
		physx::PxVec3 target = origin + rayDir * 100.0f;

		// aim from the PIVOT
		physx::PxVec3 aim = (target - physx::PxVec3{0, 0, 0}).getNormalized();

		_gun.first.q = lookRotation(aim);
		_gun.first.p = physx::PxVec3{ 0, 0, 0 } + aim * 2.0f;   // center = pivot + half length forward

		setDirection(aim);
		_configs[_currConfigIndex].direction = aim;
		_configs[_currConfigIndex].position.p = _gun.first.p + aim * _size.z();
	}
}

void GunManager::addBulletConfig(BulletConfig b) {
	_configs.push_back(b);
}

void GunManager::changeConfig() {
	_currConfigIndex = (_currConfigIndex + 1) % _configs.size();
}

void GunManager::spawnParticle(ParticleSystem& pSys) {
	Particle* p = pSys.spawn();

	BulletConfig& currConfig = _configs[_currConfigIndex];
	currConfig.direction = _dir;

	p->init(currConfig);

	p->applyForce(currConfig.direction.normalized() * currConfig.shotForce);
}

void GunManager::setDirection(Vector3D dir) {
	_dir = dir;
}

physx::PxTransform& GunManager::getGunTransform() {
	return _gun.first;
}