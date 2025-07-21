#pragma once
#include "Task.h"
#include "PlayerStatus.h"

//UIƒNƒ‰ƒX
class Gui 
{
public:
    Gui() = default;
    ~Gui()  = default;
    void Initialize();
    void Finalize();
    void Update(const PlayerStatus& player, const int liveBlockNum);
    void Draw() const;
    void SetterStageNum(int stageNum) { _stageNum = stageNum; };
private:
    PlayerStatus _drawnStatus;
    bool _isPhase1;
    bool _isPhase2;
    bool _isPhase3;
    int _liveNum;
    int _stageNum;
};

