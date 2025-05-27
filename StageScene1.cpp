#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "eBulletSize.h"
#include "SoundManager.h"
#include "ResourceLoader.h"
#include "ResourceID.h"
#include "Stage1Script.h"

using namespace std;

StageScene1::StageScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractScene(impl, param) , _cnt(0){
	_blockMgr = make_shared<BlockMgr>();
	_bulletMgr = make_shared<BulletMgr>();
	_gameMgr = make_shared<GameMgr>(dynamic_cast<IGameLifeCycleHandler*>(this));
	_colMgr = make_shared<ColMgr>();

	_player = make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_ball = make_shared<Ball>(Define::BALL_INIX, Define::BALL_INIY);
	
	//_stageScript = make_unique<Stage1Script>("Stage1SpellScript.json", "Stage1SpellCommand.json");
	_stageScript = make_unique<Stage1Script>("Stage1Script.json", "Stage1Command.json");
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
	

	//Vector2<float> injectionPoint2(Define::SCREEN_WIDTH, Define::PLAYER_INIY - 50);
	////かなり高いところ
	//Vector2<float> injectionPoint3(0, Define::SCREEN_HEIGHT/3);
	//Vector2<float> injectionPoint4(Define::SCREEN_WIDTH, Define::SCREEN_HEIGHT/3 - 50);
	////低いところ
	//Vector2<float> injectionPoint5(0, Define::SCREEN_HEIGHT - 10);

	//ballが待ち状態、Playerのlifeが0以下、blockが一つもない時は弾幕を発生させない
	if (!_ball->CheckFlag((int)Ball::fBall::_wait) && (_player->Getter_PlayerLife() >0) && (_blockMgr->Getter_LiveNum() >0)) {
		//ポインタを入れてnullではないかどうかを確認している
		if (_stageScript) {
			_stageScript->Update(_cnt, *_bulletMgr, *_player, *_ball);
		}

		_cnt++;
	}


	//もしplayerのlifeが0以下なら
	if (_player->Getter_PlayerLife() <= 0) {
		SoundManager::getIns()->stop(toString(ResourceID::Stage1));
	}
	

	_gameMgr->Update(*_blockMgr, *_bulletMgr, *_player, *_ball);
	_colMgr->Update(*_blockMgr, *_bulletMgr, *_player, *_ball);
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

	SoundManager::getIns()->play(toString(ResourceID::Stage1), true);
}

void StageScene1::RequestClear() {
	SoundManager::getIns()->stop(toString(ResourceID::Stage1));
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

	SoundManager::getIns()->play(toString(ResourceID::Stage1), true);
}