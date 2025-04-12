#pragma once
#include "AbstractScene.h"
#include "ISceneChangedListener.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include "GameMgr.h"

#include <memory>

class StageScene1 :
    public AbstractScene
{
public:
    StageScene1(ISceneChangedListener* impl, const Parameter& param);
    ~StageScene1() = default;

    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

private:
    std::shared_ptr<BlockMgr> _blockMgr;
    std::shared_ptr<BulletMgr> _bulletMgr;

    std::shared_ptr<GameMgr> _gameMgr;

    int _cnt;

};

