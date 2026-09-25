#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, Vector3 a);
	~Particle();

	void integrate(double t);

private:
	Vector3D vel;
	physx::PxTransform pose;
	Vector3D a;
	float damping = 1;
	RenderItem* renderItem;
};

