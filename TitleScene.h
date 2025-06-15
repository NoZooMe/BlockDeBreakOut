#pragma once
#include "AbstractScene.h"
#include "Choices.h"
#include "EffectPipeline.h"
#include <string>
#include <memory>

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

private:
    std::shared_ptr<Choices> _titleMenu;
    std::shared_ptr<EffectPipeline> _effectPipeline;

    const static char* TitleMenu1;
    const static char* TitleMenu2;
    const static char* TitleMenu3;
    const static char* TitleMenu4;
    const static char* TitleMenu5;

    //フェードイン用
    int _alpha;
    int _fadeInTime;
    int _frameCnt;
    bool _isInputEnabled;
    bool _postEnabled;

    bool _isTutorial;
    bool _isConfig;

    int _volume;
    int _volumeRate;
};

