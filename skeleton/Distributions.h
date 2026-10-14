#pragma once
#include <random>
#include <functional>
#include "Vector3D.h"
#include "RenderUtils.hpp"

class Distribution {
public:
	Distribution(std::function<float(std::mt19937&)> d);
	float generate();
	Vector3D generateVec3();
	Vector4 generateVec4();

protected:
	std::mt19937 _mt;
	std::function<float(std::mt19937&)> _distribution;
};