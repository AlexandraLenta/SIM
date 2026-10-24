#include "Particle.h"

Particle::Particle(float radius, Vector4 color) : radius(radius), color(color) {
	createRenderItem();
}

Particle::Particle(Particle& config) {
	radius = config.radius;
	color = config.color;
	iniColor = config.color;
	finColor = config.finColor;

	position = config.position;
	prevPosition = config.prevPosition;

	velocity = config.velocity;
	acceleration = config.acceleration; 
	force = { 0, 0, 0 };

	realMass = config.realMass;
	simulatedMass = config.simulatedMass;
	massInverse = realMass > 0.0f ? 1.f / realMass : 0.0f;
	
	realGravity = config.realGravity;
	simulatedGravity = config.simulatedGravity;
	
	damping = config.damping;

	lifetime = config.lifetime;
	age = 0.0;
	alive = true;

	std::cout << realGravity << '\n';

	createRenderItem();
}

void Particle::calculateInverseMass() {
	massInverse = simulatedMass > 0.0f ? 1.f / simulatedMass : 0.0f;
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

	clearAccumulators();
}

void Particle::integrateEulerSemiImplicit(double t) {
	if (massInverse <= 0.0f) return; // no integramos objetos con masa infinita
	
	Vector3D finalA = acceleration + Vector3D{ 0, simulatedGravity, 0 } + force * massInverse;

	velocity = (velocity + finalA * t) * pow(damping, t); // actualizar velocidad en base a aceleracion constante
	
	position.p = position.p + (velocity * t); // actualizar la posicion

	clearAccumulators();
}

void Particle::integrateVerlet(double t) {
	if (massInverse <= 0.0f) return; // no integramos objetos con masa infinita

	Vector3D finalA = acceleration + simulatedGravity + force * massInverse;

	physx::PxTransform tempPose = prevPosition;
	prevPosition = position;

	position.p = 2 * prevPosition.p - tempPose.p + finalA * t * t;

	clearAccumulators();
}

void Particle::calculateSimulatedValues() {
	if (realSpeed <= 0.0f || simulatedSpeed <= 0.0f) {
		std::cerr << "Speeds must be greater than zero\n";
		return;
	}

	simulatedMass = realMass * ((realSpeed / simulatedSpeed) * (realSpeed / simulatedSpeed));

	simulatedGravity = realGravity * ((simulatedSpeed / realSpeed) * (simulatedSpeed / realSpeed));

	massInverse = simulatedMass > 0.0f ? 1.f / simulatedMass : 0.0f;
}

void Particle::clearAccumulators() {
	force = 0;
}


void Particle::applyForce(Vector3D f) {
	force += f;
}

void Particle::update(double t) {
	if (age >= lifetime) {
		alive = false;
	}
	else {
		integrateEulerSemiImplicit(t);
		age += t;

		if (iniColor != finColor) {
			double dt = age / lifetime;
			changeColor(lerpColor(iniColor, finColor, dt));
		}
	}
}

void Particle::changeColor(Vector4 c) {
	color = c;
	renderItem->changeColor(c);
}

double Particle::lerp(double a, double b, double t) {
	if (t < 0.0 || t > 1.0) {
		throw std::out_of_range("t must be between 0 and 1 for interpolation");
	}
	return a + t * (b - a);
}

Vector4 Particle::lerpColor(Vector4 a, Vector4 b, double t) {
	if (t < 0.0) {
		return iniColor;
	}
	else if (t > 1.0) {
		return finColor;
	}

	Vector4 linearA = rgb2linear(a);
	Vector4 linearB = rgb2linear(b);

	Vector4 interpolated = linearA + (linearB - linearA) * t;

	return linear2rgb(interpolated);
}

float Particle::rgb2linear(float s) {
	return s <= 0.04045f
		? s / 12.92f
		: powf((s + 0.055f) / 1.055f, 2.4f);
}

float Particle::linear2rgb(float linear) {
	return linear <= 0.0031308f
		? linear * 12.92f
		: 1.055f * powf(linear, 1.0f / 2.4f) - 0.055f;
}

Vector4 Particle::rgb2linear(Vector4 c) {
	return {
		rgb2linear(c.x),
		rgb2linear(c.y),
		rgb2linear(c.z),
		c.w
	};
}

Vector4 Particle::linear2rgb(Vector4 c) {
	return {
		linear2rgb(c.x),
		linear2rgb(c.y),
		linear2rgb(c.z),
		c.w
	};
}