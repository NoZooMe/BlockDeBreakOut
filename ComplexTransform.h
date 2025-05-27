#pragma once
#include <complex>
#include <unordered_map>
#include <string>

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
	~ComplexTransform() = delete;
private:
	//状態を持つ必要が無いなら静的なメンバで。
	static const std::unordered_map<SpaceTransformMode, std::string> _modeToStr;
	static std::complex<float> Gamma(std::complex<float> z);
	static std::complex<float> Zeta_Dirichlet(std::complex<float> s, int terms);
	static std::complex<float> Zeta_Approx(std::complex<float> s, int N);
	static std::complex<float> Zeta(std::complex<float> s);
};

