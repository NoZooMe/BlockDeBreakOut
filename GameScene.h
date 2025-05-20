#pragma once
#include "AbstractScene.h"
#include "Choices.h"
#include "StageScene1.h"
#include "ISceneChangedListener.h"
#include <memory>
class GameScene :
    public AbstractScene, public ISceneChangedListener
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
    void exitGame() override;

private:
    int _level;
    std::shared_ptr<Choices> _gameMenu;
    std::shared_ptr<StageScene1> _stageScene1;

    const static char* GameMenu1;
    const static char* GameMenu2;

    bool pose;
};

