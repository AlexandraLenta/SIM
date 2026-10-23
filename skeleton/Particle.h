#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

struct Particle {
	float radius;
	Vector4 color;
	Vector4 iniColor;
	Vector4 finColor;

	physx::PxTransform position;
	physx::PxTransform prevPosition;

	Vector3D velocity;
	Vector3D acceleration;
	Vector3D force = { 0, 0, 0 };
	
	float realMass;
	float simulatedMass;
	float massInverse;
	
	float realSpeed;
	float simulatedSpeed;
	
	float realGravity;
	float simulatedGravity;
	
	float damping = 1;

	bool alive = true;
	double lifetime;
	double age = 0.0;

	Particle() = default;
	Particle(float radius, Vector4 color);
	Particle(Particle& config);
	~Particle();

	void createRenderItem();

	void update(double t);

	void integrateEuler(double t);
	void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);

	void calculateSimulatedValues();
	void calculateInverseMass();
	void init();

	void applyForce(Vector3D force);

	void changeColor(Vector4 c);
	double lerp(double a, double b, double t);
	Vector4 lerpColor(Vector4 a, Vector4 b, double t);

private:

	void clearAccumulators();

	float rgb2linear(float s);
	float linear2rgb(float linear);
	Vector4 rgb2linear(Vector4 c);
	Vector4 linear2rgb(Vector4 c);

	RenderItem* renderItem;
};