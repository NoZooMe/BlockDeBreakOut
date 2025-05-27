#pragma once
#include "AbstractScene.h"
#include "ISceneChangedListener.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include "GameMgr.h"
#include "ColMgr.h"
#include "IGameLifecycleHandler.h"
#include "StageScriptBase.h"

#include <memory>

class StageScene1 :
    public AbstractScene, public IGameLifeCycleHandler
{
public:
    StageScene1(ISceneChangedListener* impl, const Parameter& param);
    ~StageScene1() = default;

    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

    void RequestRestart() override;
    void RequestContinue() override;
    void RequestDamage() override;
    void RequestClear() override;

private:
    std::shared_ptr<BlockMgr> _blockMgr;
    std::shared_ptr<BulletMgr> _bulletMgr;
    std::shared_ptr<GameMgr> _gameMgr;
    std::shared_ptr<ColMgr> _colMgr;
    std::shared_ptr<Player> _player;
    std::shared_ptr<Ball> _ball;
    //スクリプトを持つのはそのステージだけなのでunique
    std::unique_ptr<StageScriptBase> _stageScript;


    int _cnt;



};

