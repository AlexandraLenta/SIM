#include "Particle.h"

Particle::Particle(float radius) {
	// crear la particula visualmente
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(radius));
	renderItem = new RenderItem(shape, &position, Vector4(1, 0, 0, 1));

	//calculateSimulatedValues();
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}


void Particle::integrateEuler(double t) {
	position.p = position.p + (velocity * t); // actualizar la posicion

	velocity = (velocity + acceleration * t) * pow(damping, t); // actualizar velocidad en base a aceleracion constante

	acceleration = 0; // resetear la aceleracion despues del empuje
}

void Particle::integrateEulerSemiImplicit(double t) {
	acceleration = {0, simulatedGravity, 0};
	velocity = velocity .normalized() * simulatedSpeed;

	velocity = (velocity + acceleration * t) * pow(damping, t); // actualizar velocidad en base a aceleracion constante

	position.p = position.p + (velocity * t); // actualizar la posicion

	acceleration = 0; // resetear la aceleracion despues del empuje
}

void Particle::integrateVerlet(double t) {
	physx::PxTransform tempPose = prevPosition;
	prevPosition = position;

	position.p = 2 * prevPosition.p - tempPose.p + acceleration * t * t;

	acceleration = 0; // resetear la aceleracion despues del empuje
}

void Particle::calculateSimulatedValues() {

	simulatedMass = realMass * ((realSpeed / simulatedSpeed) * (realSpeed / simulatedSpeed));

	simulatedGravity = realGravity * ((simulatedSpeed / realSpeed) * (simulatedSpeed / realSpeed));
	std::cout << simulatedGravity << '\n';
}