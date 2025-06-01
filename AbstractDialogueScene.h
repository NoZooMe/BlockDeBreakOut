#pragma once
#include "AbstractScene.h"
#include "DialogueScriptLoader.h"
class AbstractDialogueScene :
    public AbstractScene
{
public:
    AbstractDialogueScene(ISceneChangedListener* impl, const Parameter& param);
    ~AbstractDialogueScene() = default;

    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;
    bool isFinished() const;

    virtual void InitDialogueScript() = 0;
    virtual void CallSceneChange() = 0;

protected:
    std::vector<DialogueEntry> _dialogues;
    size_t _currentIndex = 0;
    bool _finished = false;

    //グラフィック
    int _leftImageHandle = -1;
    int _rightImageHandle = -1;
    std::string _currentText;
};

