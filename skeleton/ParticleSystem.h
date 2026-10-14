#pragma once
#include "Vector3D.h"
#include <vector>
#include "ParticleGenerator.h"
#include "Particle.h"

// NOTES
//for (int i = 0; i < toEmit; ++i) {
//			size_t idx = findDeadParticle();
//			if (idx < MAX_PARTICLES) {
//				m_particles[idx] = m_emitter.spawn();
//			}
//		}
//	dead particles at the end of the array, alive at the start, therefore index separates them
// 
// 
// 
// for (size_t i = 0; i < MAX_PARTICLES; ++i) {
//Particle& p = m_particles[i];
//if (!p.alive) continue;
//
//// Emitter physics
//m_emitter.applyPhysics(p, dt);
//
//// Mouse interaction
//if (m_mouseAttract || m_mouseRepel) {
//    sf::Vector2f toMouse = m_mousePos - p.position;
//    float dist = length(toMouse);
//    if (dist > 1.f && dist < 400.f) {
//        sf::Vector2f dir = normalize(toMouse);
//        float strength = mouseForce * (1.f - dist / 400.f);
//        if (m_mouseRepel) strength = -strength * 1.5f;
//        p.velocity += dir * strength * dt;
//    }
//}
//
//p.update(dt);
//
//// Soft boundary bounce
//float r = p.getRadius();
//if (p.position.x < r) { p.position.x = r; p.velocity.x *= -0.5f; }
//if (p.position.x > (float)m_windowW - r) { p.position.x = (float)m_windowW - r; p.velocity.x *= -0.5f; }
//if (p.position.y < r) { p.position.y = r; p.velocity.y *= -0.5f; }
//if (p.position.y > (float)m_windowH - r) { p.position.y = (float)m_windowH - r; p.velocity.y *= -0.5f; }
//
//++m_activeCount;
//        }
// 
// this would be in case i want maybe to make some mouse interaction
// 
// 
// AND this below is the update. the particle here is a struct
//     void update(float dt) {
//if (!alive) return;
//velocity += acceleration * dt;
//velocity *= drag;
//position += velocity * dt;
//age += dt;
//if (age >= lifetime) alive = false;
//    }
//
//    // Color shifts with age: bright → saturated → fades
//    sf::Color getColor() const {
//        float t = normalizedAge();
//        float alpha = 1.f;
//        // Fade in first 5%, fade out last 30%
//        if (t < 0.05f) alpha = t / 0.05f;
//        else if (t > 0.7f) alpha = 1.f - (t - 0.7f) / 0.3f;
//        // Hue shifts over lifetime
//        float h = std::fmod(hue + t * 60.f, 360.f);
//        float s = lerp(0.8f, 1.0f, t);
//        float v = lerp(1.0f, 0.6f, t);
//        return hsvToRgb(h, s, v, clamp(alpha, 0.f, 1.f));
//    }
// 
// // ─── Emitter class ─────────────────────────────────────────────────────────────
//class Emitter {
//public:
//    sf::Vector2f   position;
//    EmitterType    type = EmitterType::Point;
//    ColorPalette   palette = ColorPalette::NeonCyan;
//    PhysicsMode    physics = PhysicsMode::Normal;
//    float          emitRate = 200.f;   // particles per second
//    float          particleLife = 2.5f;    // seconds
//    float          speed = 200.f;   // initial speed
//    float          spread = 360.f;   // emission cone angle (degrees)
//    float          baseSize = 3.5f;
//    float          ringRadius = 80.f;    // for Ring emitter
//    float          lineLength = 300.f;   // for Line emitter
//    float          burstCooldown = 0.5f;    // for Burst emitter
//    float          vortexStrength = 300.f;
//
//    Emitter() = default;
//    Emitter(sf::Vector2f pos, EmitterType t) : position(pos), type(t) {}
//
//    // Spawn a single particle
//    Particle spawn() const {
//        Particle p;
//        p.alive = true;
//        p.age = 0.f;
//        p.lifetime = particleLife * randFloat(0.7f, 1.3f);
//        p.size = baseSize * randFloat(0.6f, 1.4f);
//        p.drag = randFloat(0.96f, 0.995f);
//
//        float baseHue = paletteBaseHue(palette);
//        float range = paletteHueRange(palette);
//        p.hue = baseHue + randFloat(-range, range);
//
//        // Position & velocity based on emitter type
//        float angle;
//        switch (type) {
//        case EmitterType::Point:
//            p.position = position;
//            angle = randFloat(0.f, spread) - spread / 2.f + 270.f; // upward default
//            angle = angle * 3.14159f / 180.f;
//            p.velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed * randFloat(0.5f, 1.5f);
//            break;
//
//        case EmitterType::Ring: {
//            float a = randFloat(0.f, 360.f) * 3.14159f / 180.f;
//            float r = ringRadius * randFloat(0.9f, 1.1f);
//            p.position = position + sf::Vector2f(std::cos(a), std::sin(a)) * r;
//            // Velocity outward from ring center
//            sf::Vector2f dir = normalize(p.position - position);
//            p.velocity = dir * speed * randFloat(0.3f, 1.0f);
//            break;
//        }
//
//        case EmitterType::Line: {
//            float offset = randFloat(-lineLength / 2.f, lineLength / 2.f);
//            p.position = position + sf::Vector2f(offset, 0.f);
//            p.velocity = sf::Vector2f(randFloat(-30.f, 30.f), -speed * randFloat(0.5f, 1.5f));
//            break;
//        }
//
//        case EmitterType::Burst:
//            p.position = position + sf::Vector2f(randFloat(-5.f, 5.f), randFloat(-5.f, 5.f));
//            angle = randFloat(0.f, 360.f) * 3.14159f / 180.f;
//            p.velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed * randFloat(0.8f, 2.0f);
//            p.lifetime *= 0.6f; // shorter-lived
//            break;
//
//        case EmitterType::Vortex: {
//            float a = randFloat(0.f, 360.f) * 3.14159f / 180.f;
//            float r = randFloat(10.f, 60.f);
//            p.position = position + sf::Vector2f(std::cos(a), std::sin(a)) * r;
//            // Tangential velocity (perpendicular to radial)
//            sf::Vector2f radial = normalize(p.position - position);
//            sf::Vector2f tangent(-radial.y, radial.x);
//            p.velocity = tangent * speed * randFloat(0.5f, 1.2f) + radial * speed * 0.2f;
//            break;
//        }
//
//        default:
//            p.position = position;
//            p.velocity = sf::Vector2f(randFloat(-speed, speed), randFloat(-speed, speed));
//            break;
//        }
//

class ParticleSystem
{
public:
	static constexpr size_t MAX_PARTICLES = 100;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos">Position of the </param>
	/// <param name="config"></param>
	ParticleSystem(Vector3D pos, Particle config);

	void update(double t);

	//void addGenerator(ParticleGenerator gen);

private:
	std::vector<Particle*> _particles;
	Particle _particleConfig;
};
