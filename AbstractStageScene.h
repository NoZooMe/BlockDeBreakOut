#pragma once
#include "AbstractScene.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include "GameMgr.h"
#include "ColMgr.h"
#include "ItemMgr.h"
#include "CollisitonEvent.h"
#include "IGameLifecycleHandler.h"
#include "StageScriptBase.h"
#include "Gui.h"
#include "EffectPipeline.h"

enum class ResourceID;

#include <memory>
class AbstractStageScene :
    public AbstractScene, public IGameLifeCycleHandler
{
public:
    AbstractStageScene(ISceneChangedListener* impl, const Parameter& param);
    ~AbstractStageScene() = default;

    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

    void RequestRestart() override;
    void RequestContinue() override;
    void RequestDamage() override;
    void RequestClear() override;
    void RequestGameOver() override;

protected:
    virtual void InitStageScript() = 0;
    virtual void UpdateStageScript(int cnt) = 0;
    virtual ResourceID GetStageBGM() const = 0;
    virtual void ChangeCurrentScript(int BlockNum) = 0;

    std::shared_ptr<BlockMgr> _blockMgr;
    std::shared_ptr<BulletMgr> _bulletMgr;
    std::shared_ptr<GameMgr> _gameMgr;
    std::shared_ptr<ColMgr> _colMgr;
    std::shared_ptr<ItemMgr> _itemMgr;
    std::shared_ptr<Player> _player;
    std::shared_ptr<Ball> _ball;
    std::shared_ptr<Gui> _gui;
    std::shared_ptr<EffectPipeline> _effectPipeline;

    int _cnt;
    int _currentScriptIndex;
    int _beginCnt;
    int _clearCnt;
    int _damageCnt;
    bool _isClear;
    bool _isGameOver;
    bool _isDamage;


    std::vector<std::unique_ptr<StageScriptBase>> _stageScript;
    std::vector<CollisionEvent> _colEvArray;
};

