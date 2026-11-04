#pragma once
#include <vector>
#include "Particle.h"

class ParticleSystem;

struct BulletConfig {
	float radius = 2;
	Vector4 color = { 0, 0, 0, 1 };
	Vector4 iniColor = { 0, 0, 0, 1 };
	Vector4 finColor = { 0, 0, 0, 1 };

	physx::PxTransform position = { 0, 0, 0 };

	Vector3D direction = { 0, 0, 0 };

	float realMass = 2;

	float realSpeed = 20;
	float simulatedSpeed = 2;

	float realGravity = -9.8;

	float damping = 1;

	double lifetime = 10;

	float shotForce = 10;
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
	GunManager();

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

private:
	std::vector<BulletConfig> _configs;
	int _currConfigIndex = 0;
};