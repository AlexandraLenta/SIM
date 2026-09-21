#pragma once

#include <PxPhysicsAPI.h>
#include <iostream>

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

	float x() const {
		return _x;
	}

	float y() const {
		return _y;
	}

	float z() const {
		return _z;
	}

	float magnitude() const {
		return sqrt(_x * _x + _y * _y + _z * _z);
	}

	Vector3D normalized() const {
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

	static float dot(const Vector3D& v1, const Vector3D& v2) {
		return v1.dot(v2);
	}

	static Vector3D cross(const Vector3D& v1, const Vector3D& v2) {
		return v1.cross(v2);
	}

	bool operator==(const Vector3D& other) {
		return _x == other._x && _y == other._y && _z == other._z;
	}

	Vector3D& operator=(const Vector3D& other) {
		_x = other._x;
		_y = other._y;
		_z = other._z;
		return *this;
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

	operator physx::PxVec3() const {
		return physx::PxVec3(_x, _y, _z);
	}

};

inline std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
	os << '{' << v.x() << ',' << v.y() << ',' << v.z() << '}';
	return os;
}