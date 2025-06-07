#include "AbstractStageScene.h"
#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "Keyboard.h"
#include "ResourceID.h"
#include "SoundManager.h"
#include "ResourceLoader.h"

using namespace std;

AbstractStageScene::AbstractStageScene(ISceneChangedListener* impl, const Parameter& param) :
	AbstractScene(impl, param), _cnt(0) {
	_blockMgr = make_shared<BlockMgr>();
	_bulletMgr = make_shared<BulletMgr>();
	_gameMgr = make_shared<GameMgr>(dynamic_cast<IGameLifeCycleHandler*>(this));
	_colMgr = make_shared<ColMgr>();
	_itemMgr = make_shared<ItemMgr>();

	_player = make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_ball = make_shared<Ball>(Define::BALL_INIX, Define::BALL_INIY);


	_gui = make_shared<Gui>();
}

void AbstractStageScene::Initialize() {
	_bulletMgr->Initialize();
	_colMgr->Initialize();
	_itemMgr->Initialize();
	_gameMgr->Initialize();
	_blockMgr->Initialize();

	_player->Initialize();
	_ball->Initialize();

	_gui->Initialize();

	InitStageScript();

	SoundManager::getIns()->load(toString(GetStageBGM()), ResourceLoader::getIns()->getSoundPath(toString(GetStageBGM())));
	SoundManager::getIns()->play(toString(GetStageBGM()), true);
}

void AbstractStageScene::Finalize() {
	_gameMgr->Finalize();
	_blockMgr->Finalize();
	_bulletMgr->Finalize();
	_colMgr->Finalize();
	_itemMgr->Finalize();

	_player->Finalize();
	_ball->Finalize();

	_gui->Finalize();

	SoundManager::getIns()->stop(toString(GetStageBGM()));
	SoundManager::getIns()->release(toString(GetStageBGM()));
}

void AbstractStageScene::Update() {

	//ballが待ち状態、Playerのlifeが0以下、blockが一つもない時は弾幕を発生させない
	if (!_ball->CheckFlag((int)Ball::fBall::_wait) && (_player->Getter_PlayerLife() > 0) && (_blockMgr->Getter_LiveNum() > 0)) {
		//ポインタを入れてnullではないかどうかを確認している
		if (_stageScript) {
			UpdateStageScript(_cnt);
		}

		_cnt++;
	}


	//もしplayerのlifeが0以下なら
	if (_player->Getter_PlayerLife() <= 0) {
		SoundManager::getIns()->stop(toString(GetStageBGM()));
	}

	_colMgr->Update(*_blockMgr, *_bulletMgr, *_itemMgr, *_player, *_ball, _colEvArray);
	_gameMgr->Update(*_blockMgr, *_bulletMgr, *_itemMgr, *_player, *_ball, _colEvArray);
	_gui->Update(_player->Getter_Status());

	_colEvArray.clear();
}

void AbstractStageScene::Draw() const {
	_gameMgr->Draw(*_blockMgr, *_bulletMgr, *_itemMgr, *_player, *_ball);
	_gui->Draw();
	_itemMgr->Draw();
}

void AbstractStageScene::RequestDamage() {
	_ball->Finalize();
	_ball = std::make_shared<Ball>(_player->GetterPosX(), _player->GetterPosY() - (Define::BALL_RADIUS + Define::PLAYER_HEIGHT / 2));
	_ball->Initialize();
}

void AbstractStageScene::RequestContinue() {
	_player->Finalize();
	_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_player->Initialize();

	_ball->Finalize();
	_ball = std::make_shared<Ball>(_player->GetterPosX(), _player->GetterPosY() - (Define::BALL_RADIUS + Define::PLAYER_HEIGHT / 2));
	_ball->Initialize();

	_bulletMgr->Finalize();
	_bulletMgr = std::make_shared<BulletMgr>();
	_bulletMgr->Initialize();

	SoundManager::getIns()->play(toString(GetStageBGM()), true);
}

void AbstractStageScene::RequestClear() {
	SoundManager::getIns()->stop(toString(GetStageBGM()));
}

void AbstractStageScene::RequestRestart() {
	_player->Finalize();
	_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_player->Initialize();

	_ball->Finalize();
	_ball = std::make_shared<Ball>(_player->GetterPosX(), _player->GetterPosY() - (Define::BALL_RADIUS + Define::PLAYER_HEIGHT / 2));
	_ball->Initialize();

	_bulletMgr->Finalize();
	_bulletMgr = std::make_shared<BulletMgr>();
	_bulletMgr->Initialize();

	_blockMgr->Finalize();
	_blockMgr = std::make_shared<BlockMgr>();
	_blockMgr->Initialize();

	_itemMgr->Finalize();
	_itemMgr = std::make_shared<ItemMgr>();
	_itemMgr->Initialize();

	SoundManager::getIns()->play(toString(GetStageBGM()), true);
}