#pragma once

#include "IEffect.h"
#include <memory>
#include <vector>
#include <functional>

class EffectPipeline
{
public:
	EffectPipeline(int w, int h);
	void AddShakeEffect(int duration, int amplitube);
	void AddWaveEffect(int duration, float frequency, float speed, int amplitude);
	void AddWhiteFlashEffect(int duration);
	void Draw(const std::function<void()>& drawFunc) const;
	void Initialize();
	void Finalize();
	void Update();

private:
	void Clear();
	std::vector<std::shared_ptr<IEffect>> _effects;
	int _bufferA;
	int _bufferB;
	int _w, _h;
};

