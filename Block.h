#pragma once
#include "RectangleObject.h"
class Block :
    public RectangleObject
{
private:
    int color;
    
public:
    Block(float x, float y, float width, float height, int color);
    void Init() override;
    void Fin() override;
    void Update() override;
    void Draw() const;

    enum class fBlock {
        _live,
    };

    void SetBlockFlag_Live(bool value);
};

