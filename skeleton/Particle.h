#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3D pos = { 0, 0, 0 }, Vector3D dir = { 0, 0, 0 }, Vector3D a = { 0, 0, 0 }, float life = 10, Vector4 color = {0, 0, 0, 1}, float mR = 5, float sR = 30, float sS = 25, float d = 1);
	~Particle();

	void integrateEuler(double t);
	virtual void integrateEulerSemiImplicit(double t);
	void integrateVerlet(double t);
	 
	void setPos(Vector3D p);
	void setPos(physx::PxTransform p);

	void setDir(Vector3D v);
	void setRealSpeed(float s);
	void setAcceleration(Vector3D a);
	
	void setGravity(float y);

protected:
	physx::PxTransform _pose;
	physx::PxTransform _previousPose;
	
	Vector3D _vel;
	Vector3D _a;
	float _damping; // por defecto sin damping

	float _realMass;
	float _simulatedMass;

	float _realSpeed;
	float _simulatedSpeed;

	float _realGravity;
	float _simulatedGravity;

	Vector4 _color;
	
	float _lifetime;

	void calculateSimulatedValues();

	RenderItem* _renderItem;
};