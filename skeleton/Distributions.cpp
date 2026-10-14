#include "Distributions.h"

Distribution::Distribution(std::function<float(std::mt19937&)> d) : _mt(std::random_device()()), _distribution(std::move(d)) {}

float Distribution::generate() {
	return _distribution(_mt);
}

Vector3D Distribution::generateVec3() {
	return { generate(), generate(), generate() };
}

Vector4 Distribution::generateVec4() {
	return { generate(), generate(), generate(), generate() };
}