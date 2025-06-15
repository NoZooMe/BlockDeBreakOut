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
#include "GlobalStatusManager.h"
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
	_continueCredit = Define::PLAYER_CONTINUE;
}

void GameMgr::Initialize() {
}

void GameMgr::Finalize() {
}

void GameMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, ItemMgr& itemMgr, Player& player, Ball& ball, const std::vector<CollisionEvent>& evCol) {

	//残機があるときとないときで分岐
	if (player.Getter_PlayerLife() > 0 && blockMgr.Getter_LiveNum() != 0) {//残機があるかつクリアしてないとき
		//画面外処理は各インスタンスに任せる.
		
		//プレイヤーの位置をホーミングするアイテムの為、プレイヤーの位置をitemMgrに保存。
		itemMgr.SetPlayerPosition(player.GetterPosition());

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
			//スペースボタンを押された時、ボールはplayerの方に戻る
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
				ball.WaveFlag(static_cast<int>(Ball::fBall::_move), false);
			}
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
				SoundManager::getIns()->play(toString(ResourceID::BombSE));
				
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
			if (_bombCoolCnt >= Define::PLAYER_BOMBTIME * 60) {
				_bombCoolCnt = 0;
				_isBombActive = false;
			}
		}
	}
	else if(player.Getter_PlayerLife() <= 0){//残機が無くなったら
		player.SetPlayerFlag_Death(true);
		bulletMgr.Update();

		//スペースが押されたらコンティニュー回数によって分岐
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			if (player.Getter_PlayerContinue() > 0) {
				_implLifeCycle->RequestContinue();
			}
			else {
				_implLifeCycle->RequestGameOver();
			}
		}
	}
	else if (blockMgr.Getter_LiveNum() <= 0) {//blockを全て消せたら

		//ハイスコア更新処理
		if (player.Getter_PlayerScore() >= GlobalStatusManager::getIns()->GetHighScore()) {
			GlobalStatusManager::getIns()->SetHighScore(player.Getter_PlayerScore());
		}

		bulletMgr.DeleteAllBullet();

		_implLifeCycle->RequestClear();

	}
}

void GameMgr::Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const ItemMgr& itemMgr, const Player& player, const Ball& ball) const {
	
	
	player.Draw();
	ball.Draw();
	blockMgr.Draw();
	bulletMgr.Draw();
	itemMgr.Draw();
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
		case eCollisionEvent::BallToBullet: {
			Vector2<float> temp = bulletMgr.GetBullet(ev._index)->GetterPosition();
			itemMgr.Generate(eItemName::ScoreToPlayer, temp.GetterX(), temp.GetterY());
			bulletMgr.DeleteBullet(ev._index);
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