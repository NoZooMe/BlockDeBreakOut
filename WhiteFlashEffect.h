#pragma once
#include "IEffect.h"
class WhiteFlashEffect :
    public IEffect
{
public:
    WhiteFlashEffect(int duration, int w, int h);
    void Update() override;
    void Apply(int src, int dst) override;

private:
    float _alpha;
    float _fadeSpeed;
};

