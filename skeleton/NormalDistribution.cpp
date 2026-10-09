#include "NormalDistribution.h"

NormalDistribution::NormalDistribution() : _mt(), _g(0,1) {
}

double NormalDistribution::generate() {
	return _g(_mt);
}