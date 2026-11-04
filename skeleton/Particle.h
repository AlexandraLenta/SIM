#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

struct BulletConfig;

struct Particle {
	float radius = 2;
	Vector4 color = { 0, 0, 0, 1 };
	Vector4 iniColor = { 0, 0, 0, 1 };
	Vector4 finColor = { 0, 0, 0, 1 };
	Vector4 linearIni = { 0, 0, 0, 1 };
	Vector4 linearFin = { 0, 0, 0, 1 };

	physx::PxTransform position = { 0, 0, 0 };
	physx::PxTransform prevPosition = { 0, 0, 0 };

	Vector3D velocity = { 0, 0, 0 };
	Vector3D acceleration = { 0, 0, 0 };
	Vector3D force = { 0, 0, 0 };
	
	float realMass = 2;
	float simulatedMass;
	float massInverse;
	
	float realSpeed = 20;
	float simulatedSpeed = 2;
	
	float realGravity = -9.8; 
	float simulatedGravity;
	
	float damping = 1;

	bool alive = true;
	double lifetime = 10;
	double age = 0.0;

	Particle() = default;
	Particle(float radius, Vector4 color);
	Particle(Particle& config);
	~Particle();
	
	void init(Particle& config);
	void init(BulletConfig& config);

	void createRenderItem();

	void update(double t);

	void integrateEuler(double t);
	void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);

	void calculateSimulatedValues();
	void calculateInverseMass();

	
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

	RenderItem* renderItem = nullptr;
};