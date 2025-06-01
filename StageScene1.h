#pragma once
#include "AbstractStageScene.h"

class StageScene1 :
    public AbstractStageScene
{
public:
    StageScene1(ISceneChangedListener* impl, const Parameter& param);
    ~StageScene1() = default;

private:
    void InitStageScript() override;
    void UpdateStageScript(int cnt) override;
    ResourceID GetStageBGM() const override;
};

