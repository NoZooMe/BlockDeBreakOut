#pragma once
#include "AbstractScene.h"
class GameScene :
    public AbstractScene
{
public:
    const static char* ParameterTagStage;
    const static char* ParameterTagLevel;

    GameScene(ISceneChangedListener* impl, const Parameter& parameter);
    ~GameScene() = default;

    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;
private:
    int _level;
};

