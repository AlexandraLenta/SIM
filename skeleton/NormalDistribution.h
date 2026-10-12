#pragma once
#include <random>

class NormalDistribution
{
public:
	NormalDistribution(float mean = 0, float dev = 1);
	double generate();
	
private:
	std::mt19937 _mt;
	std::normal_distribution<double> _g;
};