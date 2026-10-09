#pragma once
#include <random>

class NormalDistribution
{
public:
	NormalDistribution();
	double generate();
	
private:
	std::mt19937 _mt;
	std::normal_distribution<double> _g;
};