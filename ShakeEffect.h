#pragma once
#include "IEffect.h"
class ShakeEffect :
    public IEffect
{
public:
    ShakeEffect(int duration, int w, int h, int amplitude);
    void Apply(int src, int dst) override;
private:
    int _amplitude;
};

