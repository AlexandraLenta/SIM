#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, Vector3 a) : vel(vel), pose(pos), a(a) {
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

	vel = (vel + a * t) * damping;

	pose.p = pose.p + (vel * t);


	//F = 0;
}