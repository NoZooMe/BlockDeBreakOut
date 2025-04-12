#include "StageScene1.h"
#include "Macro.h"

using namespace std;

StageScene1::StageScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractScene(impl, param) , _cnt(0){
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

	Vector2<float> temp(300, 300);

	if (_cnt % 60 == 0) {
		_bulletMgr->Set_SinSmallBullet(temp, _gameMgr->GetterPlayerPosition(), 10, 1);
		_bulletMgr->Set_StraightSmallBullet(temp, _gameMgr->GetterPlayerPosition(), 10, 1);
	}

	_cnt++;

}

void StageScene1::Draw() const {
	_blockMgr->Draw();
	_bulletMgr->Draw();
	_gameMgr->Draw();
}