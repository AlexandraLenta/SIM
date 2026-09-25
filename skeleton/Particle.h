#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3D pos = { 0, 0, 0 }, Vector3D vel = { 0, 0, 0 }, Vector3D a = { 0, 0, 0 }, float d = 1);
	~Particle();

	void integrateEuler(double t);
	void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);

private:
	Vector3D vel;
	physx::PxTransform pose;
	physx::PxTransform previousPose;
	Vector3D a;
	float damping; // por defecto sin damping
	RenderItem* renderItem;
};

