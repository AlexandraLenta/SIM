#pragma once

#include <PxPhysicsAPI.h>

class Vector3D
{
private:
	float _x, _y, _z;

public:

	Vector3D(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z) {};
	Vector3D(physx::PxVec3 physVec) noexcept {
		_x = physVec.x;
		_y = physVec.y;
		_z = physVec.z;
	}

	float x() {
		return _x;
	}

	float y() {
		return _y;
	}

	float z() {
		return _z;
	}

	float magnitude() const {
		return sqrt(_x * _x + _y * _y + _z * _z);
	}

	Vector3D normalize() const {
		float mag = magnitude();
		return { _x / mag, _y / mag, _z / mag };
	}

	float dot(const Vector3D& v) const {
		return _x * v._x + _y * v._y + _z * v._z;
	}

	Vector3D cross(const Vector3D& v) const {
		float x = _y * v._z - _z * v._y;
		float y = _z * v._x - _x * v._z;
		float z = _x * v._y - _y * v._x;

		return { x, y, z };
	}

	bool operator=(const Vector3D& other) {
		return _x == other._x && _y == other._y && _z == other._z;
	}

	Vector3D operator+(const Vector3D& other) {
		return { _x + other._x, _y + other._y, _z + other._z };
	}

	Vector3D operator-(const Vector3D& other) {
		return { _x - other._x, _y - other._y, _z - other._z };
	}

	Vector3D operator*(const float a) {
		return { _x * a, _y * a, _z * a };
	}

	Vector3D& operator+=(const Vector3D& other) {
		_x += other._x;
		_y += other._y;
		_z += other._z;

		return *this;
	}

	operator physx::PxVec3() const {
		return physx::PxVec3(_x, _y, _z);
	}

	explicit operator physx::PxVec3() const {
		return physx::PxVec3(_x, _y, _z);
	}

};