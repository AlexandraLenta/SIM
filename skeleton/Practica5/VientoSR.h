#pragma once
#include "GeneradorFuerzaSR.h"

// Fuerza proporcional a la velocidad del solido relativa al aire (a mayor diferencia de velocidad, mas empuje).
class VientoSR : public GeneradorFuerzaSR {
public:
	VientoSR(Vector3 vel = Vector3(20.0f, 0.0f, 0.0f), float k1 = 0.5, float k2 = 0);

	void updateForce(SolidoRigido* solido) override;

	inline void setVelocidad(Vector3 v) { _vel = v; }
	inline Vector3 getVelocidad() const { return _vel; }

protected:
	Vector3 _vel;
	float _k1;
	float _k2;
};
