#pragma once
#include "AbstractScene.h"
#include "Choices.h"
#include "GlobalStatus.h"
#include "ResourceID.h"
#include <memory>

enum class eData {
    None, 
    Kei, 
    Matsuri, 
    Data1,
    TitleMusic, 
    Stage1Music
};

class MusiumScene :
    public AbstractScene
{
public:
    MusiumScene(ISceneChangedListener* impl, const Parameter& param);
    ~MusiumScene() = default;
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

private:
    std::shared_ptr<Choices> _choices;
    GlobalStatus _status;
    ResourceID _playingMusic;
    ResourceID _nextMusic;
    eData _selectingData;

    const static char* Music1;
    const static char* Music2;

    const static char* Data1;
    const static char* Data2;
    const static char* Data3;

    const static char* Unknown;
};

