#include "VientoSR.h"

VientoSR::VientoSR(Vector3 vel, float k1, float k2)
{
	_vel = vel;
	_k1 = k1;
	_k2 = k2;
}

void VientoSR::updateForce(SolidoRigido* solido)
{
	PxRigidDynamic* d = solido->comprobarDinamico();
	if (!d) return;

	Vector3 diff = _vel - d->getLinearVelocity();

	Vector3 forceToApply = diff * _k1 + diff * diff.magnitude() * _k2;

	d->addForce(forceToApply);
}
