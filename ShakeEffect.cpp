#include "ShakeEffect.h"
#include <DxLib.h>

ShakeEffect::ShakeEffect(int duration, int w, int h, int amplitude) : IEffect(duration, w, h), _amplitude(amplitude) {

}

void ShakeEffect::Apply(int src, int dst) {
	//-_amplitude~+_amplitude
	int dx = GetRand(_amplitude * 2 + 1) - _amplitude;
	int dy = GetRand(_amplitude * 2 + 1) - _amplitude;
	SetDrawScreen(dst);
	ClearDrawScreen();
	DrawGraph(dx, dy, src, TRUE);
}