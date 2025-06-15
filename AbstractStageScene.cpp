#include "AbstractStageScene.h"
#include "StageScene1.h"
#include "Macro.h"
#include "Define.h"
#include "Keyboard.h"
#include "ResourceID.h"
#include "SoundManager.h"
#include "ResourceLoader.h"
#include "ISceneChangedListener.h"
#include "GlobalStatusManager.h"
#include "SavedataUtils.h"

using namespace std;

AbstractStageScene::AbstractStageScene(ISceneChangedListener* impl, const Parameter& param) :
	AbstractScene(impl, param), _cnt(0), _currentScriptIndex(0), _beginCnt(0), _clearCnt(0), _isClear(false), _isGameOver(false), _isDamage(false), _damageCnt(0){
	_blockMgr = make_shared<BlockMgr>();
	_bulletMgr = make_shared<BulletMgr>();
	_gameMgr = make_shared<GameMgr>(dynamic_cast<IGameLifeCycleHandler*>(this));
	_colMgr = make_shared<ColMgr>();
	_itemMgr = make_shared<ItemMgr>();

	_player = make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_ball = make_shared<Ball>(Define::BALL_INIX, Define::BALL_INIY);

	_gui = make_shared<Gui>();

	_effectPipeline = make_shared<EffectPipeline>(Define::SCREEN_WIDTH, Define::SCREEN_HEIGHT);
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

	_effectPipeline->Initialize();

	InitStageScript();

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

	_effectPipeline->Finalize();

	SoundManager::getIns()->stop(toString(GetStageBGM()));
}

void AbstractStageScene::Update() {

	if (!_isDamage) {
		if (_beginCnt >= 120) {

			if (_beginCnt == 120) {
				SoundManager::getIns()->play(toString(GetStageBGM()), true);
			}

			//Block数で弾幕タイプを変化
			ChangeCurrentScript(_blockMgr->Getter_LiveNum());

			//ballが待ち状態、Playerのlifeが0以下、blockが一つもない時は弾幕を発生させない
			if (!_ball->CheckFlag((int)Ball::fBall::_wait) && (_player->Getter_PlayerLife() > 0) && (_blockMgr->Getter_LiveNum() > 0)) {
				//_stageScriptが空でないか確認
				if (!_stageScript.empty()) {
					UpdateStageScript(_cnt);
				}

				_cnt++;
			}


			//もしplayerのlifeが0以下なら
			if (_player->Getter_PlayerLife() <= 0) {
				SoundManager::getIns()->stop(toString(GetStageBGM()));
			}

			if (_player->TryUseBomb() && !_gameMgr->GetterBombActive()) {
				_effectPipeline->AddShakeEffect(30, 10);
			}

			_colMgr->Update(*_blockMgr, *_bulletMgr, *_itemMgr, *_player, *_ball, _colEvArray);
			_gameMgr->Update(*_blockMgr, *_bulletMgr, *_itemMgr, *_player, *_ball, _colEvArray);
			//もしもgameMgr中にstack.popされても下の関数まで処理は走るので予約popすること。
			_gui->Update(_player->Getter_Status(), _blockMgr->Getter_LiveNum());
			_effectPipeline->Update();

			_colEvArray.clear();
		}
		_beginCnt++;

		if (_isClear) {
			if (_clearCnt == 0) {
				_effectPipeline->AddWhiteFlashEffect(60);
				_effectPipeline->AddShakeEffect(60, 30);
				SoundManager::getIns()->play(toString(ResourceID::BombSE));
				int addScore = _player->Getter_PlayerLife() * 500 + 1000;
				_player->AddScore(addScore);
			}
			if (_clearCnt >= 90) {
				if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
					_implSceneChangedListener->exitGame();
				}
			}
			_clearCnt++;
		}

		if (_isGameOver) {
			_implSceneChangedListener->exitGame();
		}

		int tempLife = _player->Getter_PlayerLife();
		if (tempLife == 0) {
			_isDamage = true;
			_damageCnt = 0;
		}
	}
	else {
		if (_damageCnt == 0) {
			SoundManager::getIns()->play(toString(ResourceID::KilledSE));
			_effectPipeline->AddShakeEffect(10, 50);
		}
		if (_damageCnt == 30) {
			_isDamage = false;
			_player->CallDecLife();
		}
		_damageCnt++;
	}

}

void AbstractStageScene::Draw() const {

	if (_beginCnt == 30 || _beginCnt == 60) {
		SoundManager::getIns()->play(toString(ResourceID::SelectMenuSE));
	}

	if (_beginCnt >= 30) {

		_gui->Draw();
		if (_beginCnt >= 60) {
			_effectPipeline->Draw([&] {_itemMgr->Draw();
			_gameMgr->Draw(*_blockMgr, *_bulletMgr, *_itemMgr, *_player, *_ball); });	
		}
	}

}

void AbstractStageScene::RequestDamage() {
	_ball->Finalize();
	_ball = std::make_shared<Ball>(_player->GetterPosX(), _player->GetterPosY() - (Define::BALL_RADIUS + Define::PLAYER_HEIGHT / 2));
	_ball->Initialize();
}

void AbstractStageScene::RequestContinue() {
	int credit = _player->Getter_PlayerContinue();
	credit--;
	_player->Finalize();
	_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
	_player->Initialize();
	_player->Setter_PlayerContinue(credit);

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
	GlobalStatusManager::getIns()->SetGlobalFlag(eGlobalStatusFlag::Stage1Clear, true);

	//ノーコンならフラグをオン
	if (_player->Getter_PlayerContinue() == Define::PLAYER_CONTINUE) {
		GlobalStatusManager::getIns()->SetGlobalFlag(eGlobalStatusFlag::Stage1NoContinue, true);
	}

	_isClear = true;

}

void AbstractStageScene::RequestGameOver() {
	SoundManager::getIns()->stop(toString(GetStageBGM()));

	_isGameOver = true;
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