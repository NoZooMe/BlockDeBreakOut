#pragma once
#include "Singleton.h"
#include "GlobalStatus.h"
#include "eGlobalStatusFlag.h"

class GlobalStatusManager final :
    public Singleton<GlobalStatusManager>
{
    GlobalStatusManager();
    friend Singleton<GlobalStatusManager>;

public:
    int GetHighScore() const;
    bool GetGlobalFlag(eGlobalStatusFlag flag) const;
    GlobalStatus GetGlobalStatus() const;

    void SetHighScore(const int highScore);
    void SetGlobalFlag(eGlobalStatusFlag flag, bool value);
    void SetGlobalStatus(const GlobalStatus& saveData);

private:
    GlobalStatus _globalStatus;
};

