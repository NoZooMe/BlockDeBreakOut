#pragma once
#include "Task.h"
#include "PlayerStatus.h"

class Gui 
{
public:
    Gui() = default;
    ~Gui()  = default;
    void Initialize();
    void Finalize();
    void Update(const PlayerStatus& player);
    void Draw() const;
private:
    PlayerStatus _drawnStatus;
};

