#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"

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

	Vector2<float> injectionPoint1(0, Define::PLAYER_INIY);
	Vector2<float> injectionPoint2(Define::SCREEN_WIDTH, Define::PLAYER_INIY);

	if (_cnt%200 >= 0 && _cnt%200 <= 10) {
		_bulletMgr->Set_SinSmallBullet(injectionPoint1, _gameMgr->GetterPlayerPosition(), 10, 1);
		_bulletMgr->Set_StraightSmallBullet(injectionPoint1, _gameMgr->GetterPlayerPosition(), 10, 1);
	}
	if (_cnt % 200 >= 100 && _cnt % 200 <= 110) {
		_bulletMgr->Set_SinSmallBullet(injectionPoint2, _gameMgr->GetterPlayerPosition(), 10, 1);
		_bulletMgr->Set_StraightSmallBullet(injectionPoint2, _gameMgr->GetterPlayerPosition(), 10, 1);
	}

	_cnt++;
}

void StageScene1::Draw() const {
	_blockMgr->Draw();
	_bulletMgr->Draw();
	_gameMgr->Draw();
}