#pragma once
#include <complex>

enum class SpaceTransformMode {
	Identity, 
	Inverse, 
	Sin, 
	Exp, 
	Square
};

class ComplexTransform
{
public:
	static SpaceTransformMode mode;

	static std::complex<float> Apply(const std::complex<float>& z);
};

