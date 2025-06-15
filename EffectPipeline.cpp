#include "EffectPipeline.h"
#include "Define.h"
#include "WaveEffect.h"
#include "WhiteFlashEffect.h"
#include "ShakeEffect.h"
#include <DxLib.h>

EffectPipeline::EffectPipeline(int w, int h) : _bufferA(-1), _bufferB(-1), _w(w), _h(h){

}

void EffectPipeline::AddShakeEffect(int duration, int amplitude) {
	std::shared_ptr<ShakeEffect> shake = std::make_shared<ShakeEffect>(duration, _w, _h, amplitude);
	_effects.push_back(shake);
}

void EffectPipeline::AddWaveEffect(int duration, float frequency, float speed, int amplitude) {
	std::shared_ptr<WaveEffect> wave = std::make_shared<WaveEffect>(duration, _w, _h, frequency, speed, amplitude);
	_effects.push_back(wave);
}

void EffectPipeline::AddWhiteFlashEffect(int duration) {
	std::shared_ptr<WhiteFlashEffect> whiteFlash = std::make_shared<WhiteFlashEffect>(duration, _w, _h);
	_effects.push_back(whiteFlash);
}

void EffectPipeline::Clear() {
	_effects.clear();
}

void EffectPipeline::Update() {
	for (auto it = _effects.begin(); it != _effects.end();) {
		it->get()->Update();

		if (it->get()->GetterDeleteFlag()) {
			it = _effects.erase(it);
		}
		else {
			it++;
		}
	}
}

void EffectPipeline::Draw(const std::function<void()>& drawFunc) const {
	int front = _bufferA;
	int back = _bufferB;

	SetDrawScreen(front);
	ClearDrawScreen();
	drawFunc();

	for (auto& eff : _effects) {
		std::swap(front, back);
		eff->Apply(back, front);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, front, TRUE);

	//DrawFormatString(200, 200, Define::WHITE, "%d", _effects.size());

}

void EffectPipeline::Initialize() {
	if (_bufferA != -1) DeleteGraph(_bufferA);
	if (_bufferB != -1) DeleteGraph(_bufferB);

	_bufferA = MakeScreen(_w, _h, TRUE);
	_bufferB = MakeScreen(_w, _h, TRUE);
}

void EffectPipeline::Finalize() {
	Clear();
	if (_bufferA != -1) DeleteGraph(_bufferA);
	if (_bufferB != -1) DeleteGraph(_bufferB);
	_bufferA = -1;
	_bufferB = -1;
}