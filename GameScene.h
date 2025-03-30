#pragma once
#include "AbstractScene.h"
#include "GameMgr.h"
#include <memory>
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
    std::shared_ptr<GameMgr> gameMgr;
};

