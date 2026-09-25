#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, Vector3 a, float d) : vel(vel), pose(pos), previousPose(pose), a(a), damping(d) {
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

	pose.p = pose.p + (vel * t); // actualizar el Vec3 de PxTransform (actualizar la posicion)
	
	a = 0; // resetear la aceleracion despues del empuje
}

void Particle::integrateVerlet(double t) {
	physx::PxTransform tempPose = previousPose;
	previousPose = pose;

	pose.p = 2 * pose.p - tempPose.p + a * pow(t, 2);

	a = 0; // resetear la aceleracion despues del empuje
}