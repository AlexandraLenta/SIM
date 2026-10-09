#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D dir, Vector3D a, float life, Vector4 color, float mR, float sR, float sS, float d) : _vel(dir), _pose(pos), _previousPose(_pose), _a(a), _lifetime(life), _color(color), _damping(d), _realMass(mR), _realGravity(9.8f), _realSpeed(sR), _simulatedSpeed(sS) {
	// crear la particula visualmente
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	_renderItem = new RenderItem(shape, &_pose, Vector4(1, 0, 0, 1));

	calculateSimulatedValues();
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

void Particle::setDir(Vector3D v) {
	_vel = v;
}

void Particle::setRealSpeed(float s) {
	_realSpeed = s;
	calculateSimulatedValues();
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
	_a = { 0, -_simulatedGravity, 0 }; // resetear la aceleracion a la gravedad
	
	_vel = _vel.normalized() * _simulatedSpeed;

	_vel = (_vel + _a * t) * pow(_damping, t); // actualizar velocidad en base a aceleracion constante

	_pose.p = _pose.p + (_vel * t); // actualizar el Vec3 de PxTransform (actualizar la posicion)

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

void Particle::calculateSimulatedValues() {

	_simulatedMass = _realMass * ((_realSpeed / _simulatedSpeed) * (_realSpeed / _simulatedSpeed));

	_simulatedGravity = _realGravity * ((_simulatedSpeed / _realSpeed) * (_simulatedSpeed / _realSpeed));
}

void Particle::setGravity(float y) {
	_realGravity = y;
	calculateSimulatedValues();
}