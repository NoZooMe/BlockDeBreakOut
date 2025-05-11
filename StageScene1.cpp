#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "eBulletSize.h"
#include "SoundManager.h"
#include "ResourceLoader.h"
#include "ResourceID.h"

using namespace std;

StageScene1::StageScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractScene(impl, param) , _cnt(0){
	_blockMgr = make_shared<BlockMgr>();
	_bulletMgr = make_shared<BulletMgr>();
	_gameMgr = make_shared<GameMgr>(dynamic_cast<IGameLifeCycleHandler*>(this));
	_colMgr = make_shared<ColMgr>();

	_player = make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_ball = make_shared<Ball>(Define::BALL_INIX, Define::BALL_INIY);
}

void StageScene1::Initialize() {
	_gameMgr->Initialize();
	_bulletMgr->Initialize();
	_blockMgr->Initialize();
	_colMgr->Initialize();
	
	_player->Initialize();
	_ball->Initialize();

	SoundManager::getIns()->load(toString(ResourceID::Stage1), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::Stage1)));
	SoundManager::getIns()->play(toString(ResourceID::Stage1), true);
}

void StageScene1::Finalize() {
	_gameMgr->Finalize();
	_blockMgr->Finalize();
	_bulletMgr->Finalize();
	_colMgr->Finalize();

	_player->Finalize();
	_ball->Finalize();

	SoundManager::getIns()->stop(toString(ResourceID::Stage1));
	SoundManager::getIns()->release(toString(ResourceID::Stage1));
}

void StageScene1::Update() {
	_gameMgr->Update(*_blockMgr, *_bulletMgr, *_player, *_ball);
	_colMgr->Update(*_blockMgr, *_bulletMgr, *_player, *_ball);

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
		Vector2<float> directionPlayer = _player->GetterPosition() - injectionPoint3;
		_bulletMgr->Set_StraightBullet(eBulletSize::Midium, injectionPoint3, directionPlayer.GetterAngle(), 5, 1);
	}

	if (_cnt % 300 >= 200 && _cnt % 300 <= 205) {
		Vector2<float> directionPlayer = _player->GetterPosition() - injectionPoint4;
		_bulletMgr->Set_StraightBullet(eBulletSize::Midium, injectionPoint4, directionPlayer.GetterAngle(), 5, 1);
	}

	if (_cnt % 100 == 0) {
		_bulletMgr->Set_StraightBullet(eBulletSize::Midium, injectionPoint5, 0, 10, 1);
	}

	_cnt++;
}

void StageScene1::Draw() const {
	_gameMgr->Draw(*_blockMgr, *_bulletMgr, *_player, *_ball);
}




void StageScene1::RequestDamage() {
	_ball->Finalize();
	_ball.reset();

	_ball = std::make_shared<Ball>(_player->GetterPosX(), _player->GetterPosY() - (Define::BALL_RADIUS+Define::PLAYER_HEIGHT/2));
	_ball->Initialize();
}

void StageScene1::RequestContinue() {
	_player->Finalize();
	_player.reset();
	_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_player->Initialize();

	_ball->Finalize();
	_ball.reset();
	_ball = std::make_shared<Ball>(_player->GetterPosX(),_player->GetterPosY() - (Define::BALL_RADIUS+Define::PLAYER_HEIGHT/2));
	_ball->Initialize();

	_bulletMgr->Finalize();
	_bulletMgr.reset();
	_bulletMgr = std::make_shared<BulletMgr>();
	_bulletMgr->Initialize();


}

void StageScene1::RequestClear() {

}

void StageScene1::RequestRestart() {
	_player->Finalize();
	_player.reset();
	_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_player->Initialize();

	_ball->Finalize();
	_ball.reset();
	_ball = std::make_shared<Ball>(_player->GetterPosX(), _player->GetterPosY() - (Define::BALL_RADIUS + Define::PLAYER_HEIGHT/2));
	_ball->Initialize();

	_bulletMgr->Finalize();
	_bulletMgr.reset();
	_bulletMgr = std::make_shared<BulletMgr>();
	_bulletMgr->Initialize();

	_blockMgr->Finalize();
	_blockMgr.reset();
	_blockMgr = std::make_shared<BlockMgr>();
	_blockMgr->Initialize();
}