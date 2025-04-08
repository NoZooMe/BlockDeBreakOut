#include "StageScene1.h"
#include "Macro.h"

using namespace std;

StageScene1::StageScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractScene(impl, param) {
	_blockMgr = make_shared<BlockMgr>();
	_bulletMgr = make_shared<BulletMgr>();

	_gameMgr = make_shared<GameMgr>();
}

void StageScene1::Initialize() {
	_gameMgr->Initialize();
	_bulletMgr->Initialize();
	_blockMgr->Initialize();
}

void StageScene1::Finalize() {
	_gameMgr->Finalize();
	_blockMgr->Finalize();
	_bulletMgr->Finalize();
}

void StageScene1::Update() {
	_blockMgr->Update();
	_bulletMgr->Update();
	_gameMgr->Update(_blockMgr, _bulletMgr);
}

void StageScene1::Draw() const {
	_blockMgr->Draw();
	_bulletMgr->Draw();
	_gameMgr->Draw();
}