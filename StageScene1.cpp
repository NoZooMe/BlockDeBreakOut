#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "eBulletSize.h"

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

	//è≠ÇµçÇÇ¢Ç∆Ç±ÇÎ
	Vector2<float> injectionPoint1(0, Define::PLAYER_INIY);
	Vector2<float> injectionPoint2(Define::SCREEN_WIDTH, Define::PLAYER_INIY - 50);
	//Ç©Ç»ÇËçÇÇ¢Ç∆Ç±ÇÎ
	Vector2<float> injectionPoint3(0, Define::SCREEN_HEIGHT/3);
	Vector2<float> injectionPoint4(Define::SCREEN_WIDTH, Define::SCREEN_HEIGHT/3 - 50);
	//í·Ç¢Ç∆Ç±ÇÎ
	Vector2<float> injectionPoint5(0, Define::SCREEN_HEIGHT - 10);


	if (_cnt%200 >= 0 && _cnt%200 <= 20) {
		_bulletMgr->Set_StraightBullet(eBulletSize::Small, injectionPoint1, -Define::PI*1/12, 10, 1);

		_bulletMgr->Set_SinBullet(eBulletSize::Small, injectionPoint1, -Define::PI * 3 / 12, 10, 1);
	}
	if (_cnt % 200 >= 100 && _cnt % 200 <= 120) {
		_bulletMgr->Set_StraightBullet(eBulletSize::Small, injectionPoint2, -Define::PI * 11 / 12, 10, 1);

		_bulletMgr->Set_SinBullet(eBulletSize::Small, injectionPoint2, -Define::PI * 9 / 12, 10, 1);
	}

	if (_cnt % 300 >= 145 && _cnt % 300 <= 150) {
		Vector2<float> directionPlayer = _gameMgr->GetterPlayerPosition() - injectionPoint3;
		_bulletMgr->Set_StraightBullet(eBulletSize::Midium, injectionPoint3, directionPlayer.GetterAngle(), 5, 1);
	}

	if (_cnt % 300 >= 200 && _cnt % 300 <= 205) {
		Vector2<float> directionPlayer = _gameMgr->GetterPlayerPosition() - injectionPoint4;
		_bulletMgr->Set_StraightBullet(eBulletSize::Midium, injectionPoint4, directionPlayer.GetterAngle(), 5, 1);
	}

	if (_cnt % 100 == 0) {
		_bulletMgr->Set_StraightBullet(eBulletSize::Midium, injectionPoint5, 0, 10, 1);
	}

	_cnt++;
}

void StageScene1::Draw() const {
	_bulletMgr->Draw();
	_blockMgr->Draw();
	_gameMgr->Draw();
}