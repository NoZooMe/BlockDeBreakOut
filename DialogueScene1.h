#pragma once
#include "AbstractDialogueScene.h"
class DialogueScene1 :
    public AbstractDialogueScene
{
public:
    DialogueScene1(ISceneChangedListener* impl, const Parameter& param);
    ~DialogueScene1() = default;

    void InitDialogueScript() override;
    void CallSceneChange() override;
};

