#include "NormalDistribution.h"

NormalDistribution::NormalDistribution(float mean, float dev) : _mt(std::random_device()()), _g(mean, dev) {
}

double NormalDistribution::generate() {
	_mt = std::mt19937{ std::random_device()() };
	return _g(_mt);
}