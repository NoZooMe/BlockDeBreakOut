#include "WaveEffect.h"
#include "Define.h"
#include <cmath>
#include <DxLib.h>

WaveEffect::WaveEffect(int duration, int w, int h, float frequency, float speed, int amplitude) : IEffect(duration, w, h), _frequency(frequency), _speed(speed), _amplitude(amplitude) {

}

void WaveEffect::Apply(int src, int dst) {
	SetDrawScreen(dst);
	ClearDrawScreen();
	int t = GetNowCount();
	for (int y = 0; y < _h; y += 4) {
		float offset = _amplitude * sinf(_frequency * y + _speed * t);
		DrawRectGraphF(offset, (float)y, 0, y, _w, 4, src, TRUE);
	}
}