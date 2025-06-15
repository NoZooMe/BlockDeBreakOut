#pragma once
#include "IEffect.h"
class WaveEffect :
    public IEffect
{
public:
    WaveEffect(int duration, int w, int h, float frequency, float speed, int amplitude);
    ~WaveEffect() = default;
    void Apply(int src, int dst) override;
 
private:
    float _frequency;
    float _speed;
    int _amplitude;
};

