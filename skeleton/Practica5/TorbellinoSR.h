#pragma once
#include "GeneradorFuerzaSR.h"

// Campo de velocidades que gira en torno al eje Y que pasa por _centro, mas un empuje hacia arriba.
class TorbellinoSR : public GeneradorFuerzaSR {
public:
	TorbellinoSR(Vector3 centro = Vector3(0.0f, 0.0f, 0.0f), float intensidad = 50.0f, float upStr = 50, float k1 = 0.5, float k2 = 0);

	void updateForce(SolidoRigido* solido) override;

	inline void setCentro(Vector3 c) { _centro = c; }
	inline void setIntensidad(float i) { _intensidad = i; }

protected:
	Vector3 _centro;
	float _intensidad;
	float _intensidadArriba;
	float _k1, _k2;
};
