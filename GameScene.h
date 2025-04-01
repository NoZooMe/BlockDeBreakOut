#pragma once
#include "AbstractScene.h"
#include "GameMgr.h"
#include "Choices.h"
#include "ISceneChangedListener.h"
#include <memory>
class GameScene :
    public AbstractScene, ISceneChangedListener
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

    void onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) override;
private:
    int _level;
    std::shared_ptr<GameMgr> gameMgr;
    std::shared_ptr<Choices> _gameMenu;

    const static char* GameMenu1;
    const static char* GameMenu2;

    bool pose;
};

