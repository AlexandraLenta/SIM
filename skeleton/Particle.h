#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3D pos = { 0, 0, 0 }, Vector3D dir = { 0, 0, 0 }, Vector3D a = { 0, 0, 0 }, float d = 1);
	~Particle();

	void integrateEuler(double t);
	virtual void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);
	 
	void setPos(Vector3D p);
	void setPos(physx::PxTransform p);
	void setVel(Vector3D v);
	void setAcceleration(Vector3D a);

protected:
	physx::PxTransform _pose;
	physx::PxTransform _previousPose;
	
	Vector3D _vel;
	Vector3D _a;
	float _damping; // por defecto sin damping

	RenderItem* _renderItem;
};