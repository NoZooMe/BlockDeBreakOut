#include "WhiteFlashEffect.h"
#include "Define.h"
#include <DxLib.h>

WhiteFlashEffect::WhiteFlashEffect(int duration, int w, int h) : IEffect(duration, w, h), _alpha(255.0f){
	_fadeSpeed = _alpha / static_cast<float>(_duration);
}

void WhiteFlashEffect::Update() {
	_alpha -= _fadeSpeed;
	if (_alpha <= 0.0f) {
		_alpha = 0.0f;
		_deleteFlag = true;
	}
}

void WhiteFlashEffect::Apply(int src, int dst) {
	SetDrawScreen(dst);
	DrawGraph(0, 0, src, TRUE);

	//”’‚ðã‚©‚çd‚Ë‚é
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
	DrawBox(0, 0, _w, _h, Define::WHITE, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}