#include "Particle.h"

Particle::Particle(float radius, Vector4 color) : radius(radius), color(color) {
	createRenderItem();
}

Particle::Particle(Particle& config) {

	position = config.position;
	prevPosition = config.prevPosition;
	radius = config.radius;
	velocity = config.velocity;
	acceleration = config.acceleration;
	lifetime = config.lifetime;
	color = config.color;
	realMass = config.realMass;
	simulatedMass = config.simulatedMass;
	realGravity = config.realGravity;
	simulatedGravity = config.simulatedGravity;
	damping = config.damping;
	force = { 0, 0, 0 };
	massInverse = realMass > 0.0f ? 1.f / realMass : 0.0f;

	createRenderItem();
}

void Particle::createRenderItem() {
	// crear la particula visualmente
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(radius));
	renderItem = new RenderItem(shape, &position, color);
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}


void Particle::integrateEuler(double t) {
	if (massInverse <= 0.0f) return; // no integramos objetos con masa infinita

	Vector3D finalA = acceleration + simulatedGravity + force * massInverse;
	position.p = position.p + (velocity * t); // actualizar la posicion

	velocity = (velocity + finalA * t) * pow(damping, t); // actualizar velocidad en base a aceleracion constante

	clearAccumulator();
}

void Particle::integrateEulerSemiImplicit(double t) {
	if (massInverse <= 0.0f) return; // no integramos objetos con masa infinita

	Vector3D finalA = acceleration + simulatedGravity + force * massInverse;

	velocity = velocity.normalized() * simulatedSpeed;

	velocity = (velocity + finalA * t) * pow(damping, t); // actualizar velocidad en base a aceleracion constante

	position.p = position.p + (velocity * t); // actualizar la posicion

	clearAccumulator();
}

void Particle::integrateVerlet(double t) {
	if (massInverse <= 0.0f) return; // no integramos objetos con masa infinita

	Vector3D finalA = acceleration + simulatedGravity + force * massInverse;

	physx::PxTransform tempPose = prevPosition;
	prevPosition = position;

	position.p = 2 * prevPosition.p - tempPose.p + finalA * t * t;

	clearAccumulator();
}

void Particle::calculateSimulatedValues() {
	if (realSpeed <= 0.0f || simulatedSpeed <= 0.0f) {
		std::cerr << "Speeds must be greater than zero\n";
		return;
	}

	simulatedMass = realMass * ((realSpeed / simulatedSpeed) * (realSpeed / simulatedSpeed));

	simulatedGravity = realGravity * ((simulatedSpeed / realSpeed) * (simulatedSpeed / realSpeed));

	massInverse = realMass > 0.0f ? 1.f / realMass : 0.0f;
}

void Particle::clearAccumulator() {
	acceleration = 0;
	force = 0;
}