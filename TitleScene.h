#pragma once
#include "AbstractScene.h"
class TitleScene :
    public AbstractScene
{
public:
    TitleScene(ISceneChangedListener* impl, const Parameter& parameter);
    ~TitleScene() override;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;
};

