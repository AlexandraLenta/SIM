#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D a, float d) : vel(vel), pose(pos), previousPose(pose), a(a), damping(d) {
	// crear la particula visualmente
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(shape, &pose, Vector4(1, 0, 0, 1));
}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

void Particle::integrateEuler(double t) {
	pose.p = pose.p + (vel * t); // actualizar el Vec3 de PxTransform (actualizar la posicion)

	vel = (vel + a * t) * pow(damping, t); // actualizar velocidad en base a aceleracion constante

	a = 0; // resetear la aceleracion despues del empuje
}


void Particle::integrateEulerSemiImplicit(double t) {
	vel = (vel + a * t) * pow(damping, t); // actualizar velocidad en base a aceleracion constante

	std::cout << "past: " << pose.p;

	pose.p = pose.p + (vel * t); // actualizar el Vec3 de PxTransform (actualizar la posicion)

	std::cout << "\nnew: " << pose.p << '\n';

	a = 0; // resetear la aceleracion despues del empuje
}

void Particle::integrateVerlet(double t) {
	physx::PxTransform tempPose = previousPose;
	previousPose = pose;

	pose.p = 2 * previousPose.p - tempPose.p + a * t * t;

	//std::cout << "Past: " << tempPose.p << "\nCurrent: " << previousPose.p << "\nNew: " << pose.p << '\n';

	std::cout << previousPose.p - tempPose.p << '\n';

	a = { 0,0,0 }; // resetear la aceleracion despues del empuje
}