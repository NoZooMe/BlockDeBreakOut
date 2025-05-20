#include "GameMgr.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include <DxLib.h>
#include <optional>

using namespace std;

GameMgr::GameMgr(IGameLifeCycleHandler* impl){
	_implLifeCycle = impl;
}

void GameMgr::Initialize() {
}

void GameMgr::Finalize() {
}

void GameMgr::Update(BlockMgr& blockMgr, BulletMgr& bulletMgr, Player& player, Ball& ball) {

	//残機があるときとないときで分岐
	if (player.Getter_PlayerLife() > 0 && blockMgr.Getter_LiveNum() != 0) {//残機があるかつクリアしてないとき
		//画面外処理は各インスタンスに任せる.
		
		//Playerにも待ち状態を作ってこちらがやるのはflagのONのみにする。
		//ballが待ち状態なら動けない。弾幕、ブロックも同様。
		if (!ball.CheckFlag((int)Ball::fBall::_wait)) {
			player.Update();
			bulletMgr.Update();
			blockMgr.Update();
		}

		if (ball.CheckFlag((int)Ball::fBall::_move)) {
			ball.Update();
		}
		else {//ballがplayerに追従するとき
			ball.Update(player.GetterPosX(), player.GetterPosY() - (ball.GetterR()+Define::PLAYER_HEIGHT/2.0f));
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) != 0) {

			}

		}

		//ボールが下に落ちた時
		if (ball.CheckFlag((int)Ball::fBall::_out)) {
			_implLifeCycle->RequestDamage();
			player.CallDecLife();
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
		 //ここはStageSceneでやる
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//playerの終了と初期化処理
			_implLifeCycle->RequestRestart();
		}
	}

	
}

void GameMgr::Draw(const BlockMgr& blockMgr, const BulletMgr& bulletMgr, const Player& player, const Ball& ball) const {
	if (!player.CheckFlag((int)Player::fPlayer::_death)) {
		player.Draw();
		ball.Draw();
		blockMgr.Draw();
		bulletMgr.Draw();
	}
	

	for (int i = 0; i < player.Getter_PlayerLife(); i++) {
		DrawString(i*15, 10, "●", Define::WHITE);
	}
	DrawFormatString(0, 25, Define::WHITE, "%d", player.Getter_PlayerScore());
}