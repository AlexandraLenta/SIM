#pragma once
#include <vector>
#include "Particle.h"

class ParticleSystem;

struct BulletConfig {
	float radius = 0.5;
	Vector4 color = { 0, 0, 0, 1 };
	Vector4 iniColor = { 0, 0, 0, 1 };
	Vector4 finColor = { 0, 0, 0, 1 };

	physx::PxTransform position = { 0, 0, 0 };

	Vector3D direction = { 0, 0, 0 };

	float realMass = 2;

	float realSpeed = 50;
	float simulatedSpeed = 25;

	float realGravity = -20;

	float damping = 1;

	double lifetime = 10;

	float shotForce = 100;
};

/// <summary>
/// Holds different configs in std::vector
/// player may cycle through configs
/// when key is pressed, call shoot method of this, which is going to add to the particle
/// system the particles segun the active config, and yeah. that's it. 
/// </summary>
class GunManager
{
public:
	GunManager(Vector3D size);
	~GunManager();

	void update(double dt);

	void addBulletConfig(BulletConfig b);
	
	/// <summary>
	/// Change configuration to the next one. Circular.
	/// </summary>
	void changeConfig();

	/// <summary>
	/// Spawns a particle in the slot returned by the given ParticleSystem
	/// </summary>
	/// <param name="pSys">The particle system to spawn the particle in.</param>
	void spawnParticle(ParticleSystem& pSys);

	void setDirection(Vector3D);

	physx::PxTransform& getGunTransform();

private:
	std::vector<BulletConfig> _configs;
	Vector3D _size;
	int _currConfigIndex = 0;
	Vector3D _dir;
	std::pair<physx::PxTransform, RenderItem*> _gun;
};