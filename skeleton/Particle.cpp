#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D a, float d) : _vel(vel), _pose(pos), _previousPose(_pose), _a(a), _damping(d) {
	// crear la particula visualmente
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	_renderItem = new RenderItem(shape, &_pose, Vector4(1, 0, 0, 1));
}

Particle::~Particle() {
	_renderItem->release();
	_renderItem = nullptr;
}

void Particle::setPos(Vector3D p) {
	_pose = physx::PxTransform(p);
}

void Particle::setPos(physx::PxTransform p) {
	_pose = p;
}

void Particle::setVel(Vector3D v) {
	_vel = v;
}

void Particle::setAcceleration(Vector3D a) {
	_a = a;
}

void Particle::integrateEuler(double t) {
	_pose.p = _pose.p + (_vel * t); // actualizar el Vec3 de PxTransform (actualizar la posicion)

	_vel = (_vel + _a * t) * pow(_damping, t); // actualizar velocidad en base a aceleracion constante

	_a = 0; // resetear la aceleracion despues del empuje
}

void Particle::integrateEulerSemiImplicit(double t) {
	_vel = (_vel + _a * t) * pow(_damping, t); // actualizar velocidad en base a aceleracion constante

	std::cout << "past: " << _pose.p;

	_pose.p = _pose.p + (_vel * t); // actualizar el Vec3 de PxTransform (actualizar la posicion)

	std::cout << "\nnew: " << _pose.p << '\n';

	_a = 0; // resetear la aceleracion despues del empuje
}

void Particle::integrateVerlet(double t) {
	physx::PxTransform tempPose = _previousPose;
	_previousPose = _pose;

	_pose.p = 2 * _previousPose.p - tempPose.p + _a * t * t;

	//std::cout << "Past: " << tempPose.p << "\nCurrent: " << previousPose.p << "\nNew: " << pose.p << '\n';

	std::cout << _previousPose.p - tempPose.p << '\n';

	_a = { 0,0,0 }; // resetear la aceleracion despues del empuje
}