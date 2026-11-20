#include "SolidoRigido.h"

SolidoRigido::SolidoRigido(PxRigidActor* actor, RenderItem* renderItem, const std::string& nombre, float vidaMax)
{
	_actor = actor;
	_renderItem = renderItem;
	_nombre = nombre;
	_vida = 0.0f;
	_vidaMax = vidaMax;
}

SolidoRigido::~SolidoRigido()
{
	_renderItem->release();
	_actor->release();
}

void SolidoRigido::aplicarParPuro(Vector3 par)
{
	PxRigidDynamic* d = comprobarDinamico();
	if (d) d->addTorque(par);
}

void SolidoRigido::bloquearTraslacion()
{
	PxRigidDynamic* d = comprobarDinamico();
	if (d) d->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_X | PxRigidDynamicLockFlag::eLOCK_LINEAR_Y | PxRigidDynamicLockFlag::eLOCK_LINEAR_Z);
}

Vector3 SolidoRigido::calcularInerciaCaja(float masa, Vector3 mitades)
{
	// TODO Actividad 2: usa la formula del cuboide solido del Anexo (a partir de las semi-medidas "mitades") para
	// devolver el tensor de inercia (Ix,Iy,Iz). De momento devuelve un valor cualquiera para que compile.
	return Vector3(1.0f, 1.0f, 1.0f);
}
