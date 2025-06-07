#include "GameMgr.h"
#include "Player.h"
#include "Ball.h"
#include "BlockMgr.h"
#include "BulletMgr.h"
#include "ItemMgr.h"
#include "IGameLifecycleHandler.h"
#include "CollisitonEvent.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include "SoundManager.h"
#include "ResourceID.h"
#include "eItemName.h"
#include <DxLib.h>
#include <optional>
#include <random>

using namespace std;

GameMgr::GameMgr(IGameLifeCycleHandler* impl){
	_implLifeCycle = impl;
	_itemCnt = 0;
	_itemCntMax = 0;
	_isBombActive = false;
	_bombCoolCnt = 0;
	_dx = _dy = 0;
	_shakeScreenBuffer = MakeScreen(Define::SCREEN_WIDTH, Define::SCREEN_HEIGHT, TRUE);
	_isShake = false;
	_shakeTime = 0;
	_shakePower = 0;
	_shakeCnt = 0;
}

void GameMgr::Initialize() {
}

void GameMgr::Finalize() {
}

void GameMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol) {

	//残機があるときとないときで分岐
	if (player.Getter_PlayerLife() > 0 && blockMgr.Getter_LiveNum() != 0) {//残機があるかつクリアしてないとき
		//画面外処理は各インスタンスに任せる.
		
		//衝突処理
		CollisionProcess(blockMgr, bulletMgr, itemMgr, player, ball, evCol);
		//Playerにも待ち状態を作ってこちらがやるのはflagのONのみにする。
		//ballが待ち状態なら動けない。弾幕、ブロックも同様。
		if (!ball.CheckFlag(static_cast<int>(Ball::fBall::_wait))) {
			player.Update();
			bulletMgr.Update();
			blockMgr.Update();
			itemMgr.Update();
		}

		if (ball.CheckFlag(static_cast<int>(Ball::fBall::_move))) {
			ball.Update();
		}
		else {//ballがplayerに追従するとき
			ball.Update(player.GetterPosX(), player.GetterPosY() - (ball.GetterR()+Define::PLAYER_HEIGHT/2.0f));
		}

		//ボールが下に落ちた時
		if (ball.CheckFlag(static_cast<int>(Ball::fBall::_out))) {
			_implLifeCycle->RequestDamage();
			player.CallDecLife();
		}

		//Bomb
		if (player.TryUseBomb()) {
			if (!_isBombActive) {
				_isBombActive = true;
				player.CallDecBomb();
				ShakeScreen(40, 20);
				
				for (int i = 0; i < bulletMgr.GetBulletNum(); ++i) {
					Vector2<float> temp = bulletMgr.GetBullet(i)->GetterPosition();
					itemMgr.Generate(eItemName::ScoreToPlayer, temp.GetterX(), temp.GetterY());
				}
			}
		}

		if (_isBombActive) {
			//ボム時間中は弾幕を消し続ける
			bulletMgr.DeleteAllBullet();
			_bombCoolCnt++;
			itemMgr.SetPlayerPosition(player.GetterPosition());
			if (_bombCoolCnt >= Define::PLAYER_BOMBTIME * 60) {
				_bombCoolCnt = 0;
				_isBombActive = false;
			}
		}

		//ScreenShake
		if (_isShake) {
			_shakeCnt++;

			_dx = (rand() % _shakePower * 2) - _shakePower;
			_dy = (rand() % _shakePower * 2) - _shakePower;

			if (_shakeCnt >= _shakeTime) {
				_shakeCnt = 0;
				_isShake = false;
				_dx = _dy = 0;
			}
		}
	}
	else if(player.Getter_PlayerLife() <= 0){//残機が無くなったら
		player.SetPlayerFlag_Death(true);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Over", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Continue is Space", Define::WHITE);

		//スペースが押されたらコンティニュー
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//playerの終了と初期化処理
			_implLifeCycle->RequestContinue();
		}
	}
	else if (blockMgr.Getter_LiveNum() <= 0) {//blockを全て消せたら
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Clear!", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Restart is Spece", Define::WHITE);

		_implLifeCycle->RequestClear();

		//スペースが押されたらリスタート
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//playerの終了と初期化処理
			_implLifeCycle->RequestRestart();
		}
	}
}

void GameMgr::Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const ItemMgr& itemMgr, const Player& player, const Ball& ball) const {
	if (!player.CheckFlag((int)Player::fPlayer::_death)) {

		SetDrawScreen(_shakeScreenBuffer);
		ClearDrawScreen();

		player.Draw();
		ball.Draw();
		blockMgr.Draw();
		bulletMgr.Draw();
		itemMgr.Draw();

		SetDrawScreen(DX_SCREEN_BACK);
		DrawGraph(_dx, _dy, _shakeScreenBuffer, TRUE);
	}
}

void GameMgr::CollisionProcess(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol) {
	for (const auto& ev : evCol) {
		switch (ev._type) {
		case eCollisionEvent::BallToPlayer:
			ball.ReflectFromSurface(*ev._surface, *ev._vector);
			break;
		case eCollisionEvent::BallToBlock:
			//PowerItem効果中は反射しない
			if (!ball.CheckFlag(static_cast<int>(Ball::fBall::_power))) {
				ball.ReflectFromSurface(*ev._surface, blockMgr.Getter_LiveBlock(ev._index)->GetterVelocity());
			}
			SoundManager::getIns()->play(toString(ResourceID::BreakBlockSE));
			player.AddScore(10);
			if (ItemGenerate(itemMgr, blockMgr, ev._index)) {
				//ここアイテム生成の効果音等
			}
			blockMgr.SetBlockFlag_Live(ev._index, false);
			break;
		case eCollisionEvent::BulletToPlayer:
			//無敵でないなら無敵フラグをオン
			if (!player.isDamaged()) {
				player.CallDecLife();
				SoundManager::getIns()->play(toString(ResourceID::DamageSE));
				player.DamagePlayer();
			}
			bulletMgr.DeleteBullet(ev._index);
			break;
		case eCollisionEvent::ItemToPlayer: {	//一時変数を使うのでスコープを明示指定
			auto item = itemMgr.GetterItem(ev._index);
			if (!item) break; // nullptr

			ItemContext temp = { player, ball };
			//もしImmidiateItemならCntに値を入れる
			if (std::holds_alternative<ImmidiateItem>(itemMgr.GetterItem(ev._index)->GetterVariant())) {
				_itemCntMax = std::get<ImmidiateItem>(itemMgr.GetterItem(ev._index)->GetterVariant())._time;
			}
			itemMgr.CallEffect(ev._index, temp);
			break;
		}
		default:
			ERR("存在しない当たり判定イベントです");
			break;
		}
	}
}

bool GameMgr::ItemGenerate(ItemMgr& itemMgr, BlockMgr& blockMgr, int blockIndex) {
	std::random_device rd;		//非決定的な初期化
	std::mt19937 gen(rd());		//メルセンヌ・ツイタスタで生成器を初期化

	std::uniform_int_distribution<> dist(0, 100);

	int result = dist(gen);

	//Blockの位置を取得
	float x = blockMgr.Getter_LiveBlock(blockIndex)->GetterPosX();
	float y = blockMgr.Getter_LiveBlock(blockIndex)->GetterPosY();

	if (result < 30) {
		itemMgr.Generate(eItemName::Score, x, y);
		return true;
	}
	else if (result >= 35 && result < 45) {
		itemMgr.Generate(eItemName::PowerUp, x, y);
		return true;
	}
	else if (result >= 45 && result < 50) {
		itemMgr.Generate(eItemName::Bomb, x, y);
		return true;
	}
	return false;

}

void GameMgr::ShakeScreen(int power, int duration) {
	_shakePower = power;
	_shakeTime = duration;
	_isShake = true;
}