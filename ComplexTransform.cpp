#include "ComplexTransform.h"
#include "Define.h"
#include <DxLib.h>
#include <algorithm>

SpaceTransformMode ComplexTransform::mode = SpaceTransformMode::Identity;

std::complex<float> ComplexTransform::Apply(const std::complex<float>& z) {
	switch (mode) {
	case SpaceTransformMode::Identity:
		return z;
	case SpaceTransformMode::Inverse:
		return 1.0f / z;
	case SpaceTransformMode::Sin:
		return std::sin(z);
	case SpaceTransformMode::Cos:
		return std::cos(z);
	case SpaceTransformMode::Tan:
		return std::tan(z);
	case SpaceTransformMode::Exp:
		return std::exp(z);
	case SpaceTransformMode::Conj:
		return std::conj(z);
	case SpaceTransformMode::Sinh:
		return std::sinh(z);
	case SpaceTransformMode::Gamma:
		return Gamma(z);
	case SpaceTransformMode::Zeta:
		return Zeta(z);
	default:
		return z;
	}
}

const std::unordered_map<SpaceTransformMode, std::string> ComplexTransform::_modeToStr = {
	{ SpaceTransformMode::Identity, "Identity" },
	{ SpaceTransformMode::Inverse,  "Inverse" },
	{ SpaceTransformMode::Sin,      "Sin" },
	{ SpaceTransformMode::Cos,      "Cos" },
	{ SpaceTransformMode::Tan,      "Tan" },
	{ SpaceTransformMode::Exp,      "Exp" },
	{ SpaceTransformMode::Conj,     "Conj" },
	{ SpaceTransformMode::Sinh,     "Sinh" },
	{ SpaceTransformMode::Gamma,	"Gamma"},
	{ SpaceTransformMode::Zeta,     "Zeta"}
};

std::string ComplexTransform::ToString(SpaceTransformMode mode) {
	auto it = _modeToStr.find(mode);
	return (it != _modeToStr.end()) ? it->second : "Unkown";
}

int ComplexTransform::HSVtoRGB(float h, float s, float v) {
	float r, g, b;
	float c = v * s;
	float hp = h * 6.0f;
	float x = c * (1.0f - std::fabs(std::fmod(hp, 2.0f) - 1.0f));
	float m = v - c;

	if (0 <= hp && hp < 1) { r = c; g = x; b = 0; }
	else if (1 <= hp && hp < 2) { r = x; g = c; b = 0; }
	else if (2 <= hp && hp < 3) { r = 0; g = c; b = x; }
	else if (3 <= hp && hp < 4) { r = 0; g = x; b = c; }
	else if (4 <= hp && hp < 5) { r = x; g = 0; b = c; }
	else if (5 <= hp && hp < 6) { r = c; g = 0; b = x; }
	else { r = 0; g = 0; b = 0; }

	r += m;
	g += m;
	b += m;

	int R = std::clamp(static_cast<int>(r * 255.0f), 0, 255);
	int G = std::clamp(static_cast<int>(g * 255.0f), 0, 255);
	int B = std::clamp(static_cast<int>(b * 255.0f), 0, 255);

	return GetColor(R, G, B);
}

std::complex<float> ComplexTransform::Gamma(std::complex<float> z) {
	if (z.real() < 0.5f) {
		//リフレクション公式で解析接続
		return Define::PI / (sin(Define::PI * z) * Gamma(1.0f - z));
	}
	else {//Lanczos近似法(スターリングの高精度版)
		z -= 1.0f;
		static const float p[] = {
			 676.520368f, -1259.139216f, 771.323428f,
			-176.615029f, 12.507343f, -0.138571f,
			9.98437e-6f, 1.50563e-7f
		};
		std::complex<float> x = 0.99999994f;
		for (int i = 0; i < 8; ++i) {
			x += p[i] / (z + (float)i + 1.0f);
		}
		std::complex<float> t = z + 7.5f;
		return std::sqrt(2 * Define::PI) * std::pow(t, z + 0.5f) * std::exp(-t) * x;
	}
}

std::complex<float> ComplexTransform::Zeta_Dirichlet(std::complex<float> s, int terms = 100) {
	std::complex<float> sum = 0.0f;
	for (int n = 1; n <= terms; ++n) {
		sum += 1.0f / std::pow((float)n, s);
	}
	return sum;
}

//Euler-Maclaurin近似
std::complex<float> ComplexTransform::Zeta_Approx(std::complex<float> s, int N = 100) {
	std::complex<float> sum = 0.0f;

	for (int n = 1; n <= N; ++n) {
		sum += 1.0f / std::pow((float)n, s);
	}

	std::complex<float> correction = std::pow((float)N, 1.0f - s) / (s - 1.0f);
	std::complex<float> tail = 0.5f / std::pow((float)N, s);

	return sum + correction + tail;
}

std::complex<float> ComplexTransform::Zeta(std::complex<float> s) {
	
	if (s.real() > 1.0f) {
		return Zeta_Dirichlet(s);
	}
	else if (s.real() >= 0.2f) {	//反射公式で無限ループしそうなところはEM近似で
		return Zeta_Approx(s);
	}
	else{
		std::complex<float> oneMinusS = 1.0f - s;

		std::complex<float> gamma = Gamma(oneMinusS);
		std::complex<float> zetaCompement = Zeta(1.0f - s);	//再帰呼び出し

		//反射公式で解析接続
		return std::pow(2.0f, s) * std::pow(Define::PI, s - 1.0f) *
			std::sin(Define::PI * s / 2.0f) * gamma * zetaCompement;
	}
}