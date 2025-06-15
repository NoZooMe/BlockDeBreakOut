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
    int GetBgmVolume() const;
    int GetSeVolume() const;
    GlobalStatus GetGlobalStatus() const;

    void SetHighScore(const int highScore);
    void SetGlobalFlag(eGlobalStatusFlag flag, bool value);
    void SetBgmVolume(const int volume);
    void SetSeVolume(const int volume);
    void SetGlobalStatus(const GlobalStatus& saveData);

private:
    GlobalStatus _globalStatus;
};

