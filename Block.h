#pragma once
#include "RectangleObject.h"
class Block :
    public RectangleObject
{
private:
    int color;
    
public:
    Block(float x, float y, float _width, float _height, int color);
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const;

    enum class fBlock {
        _live,
    };

    void SetBlockFlag_Live(bool value);
};

