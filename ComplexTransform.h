#pragma once
#include <complex>
#include <unordered_map>
#include <string>

//•¡‘fŠÖ”‚ğ‘€ì‚·‚é‚½‚ß‚ÌƒNƒ‰ƒX
enum class SpaceTransformMode {
	Identity, 
	Inverse, 
	Sin,
	Cos,
	Tan,
	Exp, 
	Conj,
	Sinh,
	Gamma,
	Zeta
};

class ComplexTransform
{
public:
	static SpaceTransformMode mode;

	static std::complex<float> Apply(const std::complex<float>& z);
	static std::string ToString(SpaceTransformMode mode);
	static int HSVtoRGB(float h, float s, float v);
	~ComplexTransform() = delete;
private:
	static const std::unordered_map<SpaceTransformMode, std::string> _modeToStr;
	static std::complex<float> Gamma(std::complex<float> z);
	static std::complex<float> Zeta_Dirichlet(std::complex<float> s, int terms);
	static std::complex<float> Zeta_Approx(std::complex<float> s, int N);
	static std::complex<float> Zeta(std::complex<float> s);
};

