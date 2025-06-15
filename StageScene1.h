#pragma once
#include "AbstractStageScene.h"

class StageScene1 :
    public AbstractStageScene
{
public:
    StageScene1(ISceneChangedListener* impl, const Parameter& param);
    ~StageScene1() = default;
    void Update() override;

private:
    void InitStageScript() override;
    void UpdateStageScript(int cnt) override;
    void ChangeCurrentScript(int BlockNum) override;
    ResourceID GetStageBGM() const override;
    bool _spell1Flag;
    int _spell1Cnt;
};

