#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"

struct Particle {
	float radius;
	Vector4 color;

	physx::PxTransform position;
	physx::PxTransform prevPosition;

	Vector3D velocity;
	Vector3D acceleration;
	Vector3D force;
	
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

	void changeColor(Vector4 c);

private:

	void clearAccumulator();

	RenderItem* renderItem;
};

//class Particle
//{
//public:
//	Particle(Vector3D pos = { 0, 0, 0 }, Vector3D dir = { 0, 0, 0 }, Vector3D a = { 0, 0, 0 }, float life = 10, Vector4 color = {0, 0, 0, 1}, float mR = 5, float sR = 30, float sS = 25, float d = 1);
//	~Particle();
//
//	void integrateEuler(double t);
//	virtual void integrateEulerSemiImplicit(double t);
//	void integrateVerlet(double t);
//	 
//	void setPos(Vector3D p);
//	void setPos(physx::PxTransform p);
//
//	void setDir(Vector3D v);
//	void setRealSpeed(float s);
//	void setAcceleration(Vector3D a);
//	
//	void setGravity(float y);
//
//protected:
//	physx::PxTransform _pose;
//	physx::PxTransform _previousPose;
//	
//	Vector3D _vel;
//	Vector3D _a;
//	float _damping; // por defecto sin damping
//
//	float _realMass;
//	float _simulatedMass;
//
//	float _realSpeed;
//	float _simulatedSpeed;
//
//	float _realGravity;
//	float _simulatedGravity;
//
//	Vector4 _color;
//	
//	float _lifetime;
//
//	void calculateSimulatedValues();
//
//	RenderItem* _renderItem;
//};