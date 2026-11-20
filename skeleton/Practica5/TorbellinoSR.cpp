#include "TorbellinoSR.h"

TorbellinoSR::TorbellinoSR(Vector3 centro, float intensidad, float upStr, float k1, float k2)
{
	_centro = centro;
	_intensidad = intensidad;
	_intensidadArriba = upStr;
	_k1 = k1;
	_k2 = k2;
}

void TorbellinoSR::updateForce(SolidoRigido* solido)
{
	PxRigidDynamic* d = solido->comprobarDinamico();
	if (!d) return;

	Vector3 vel = Vector3 {
			   -(solido->getPosicion().z - _centro.z),
			   _intensidadArriba - (solido->getPosicion().y - _centro.y),
			   solido->getPosicion().x - _centro.x
	} * _intensidad;

	Vector3 diff = vel - d->getLinearVelocity();

	Vector3 forceToApply = diff * _k1 + diff * diff.magnitude() * _k2;

	d->addForce(forceToApply);
}
