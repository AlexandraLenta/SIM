#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3D pos = { 0, 0, 0 }, Vector3D vel = { 1, 0, 0 }, Vector3 a = { 0, 0, 0 }, float d = 1);
	~Particle();

	void integrateEuler(double t);
	void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);

private:
	Vector3D vel;
	physx::PxTransform pose;
	Vector3D a;
	float damping; // por defecto sin damping
	RenderItem* renderItem;
};

