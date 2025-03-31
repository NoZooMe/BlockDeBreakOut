#pragma once
#include "AbstractScene.h"
#include "Choices.h"
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

    const static char* TitleMenu1;
    const static char* TitleMenu2;
    const static char* TitleMenu3;
};

