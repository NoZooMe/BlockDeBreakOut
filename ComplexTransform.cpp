#include "ComplexTransform.h"

SpaceTransformMode ComplexTransform::mode = SpaceTransformMode::Identity;

std::complex<float> ComplexTransform::Apply(const std::complex<float>& z) {
	switch (mode) {
	case SpaceTransformMode::Identity:
		return z;
	case SpaceTransformMode::Inverse:
		return 1.0f / z;
	case SpaceTransformMode::Sin:
		return std::sin(z);
	case SpaceTransformMode::Exp:
		return std::exp(z);
	case SpaceTransformMode::Square:
		return std::conj(z);
	default:
		return z;
	}
}