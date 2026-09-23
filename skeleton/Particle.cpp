#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel) : vel(vel), pose(pos) {
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(shape, &pose, Vector4(1, 0, 0, 1));
}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

void Particle::integrate(double t) {
	//Vector3D a = g + F * w;

	//vel = (vel + a * t) * pow(d, t);

	pose.p = pose.p + (vel * t); // DUDA: no se como actualizar pose entero, solo su PxVec3, y no su PxQuat

	//F = 0;
}