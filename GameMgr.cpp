#include "GameMgr.h"
#include "Define.h"
#include "Keyboard.h"
#include <DxLib.h>


GameMgr::GameMgr() : player(std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY)), ball(std::make_shared<Ball>(Define::BALL_INIX, Define::BALL_INIY)), blockMgr(std::make_shared<BlockMgr>()) {
	
}

void GameMgr::Initialize() {
	player->Initialize();
	ball->Initialize();
	blockMgr->Initialize();
}

void GameMgr::Finalize() {
	player->Finalize();
	ball->Finalize();
	blockMgr->Finalize();
}

void GameMgr::Update() {
	//SingletonのKeyboardを更新
	Keyboard::getIns()->update();

	//残機があるときとないときで分岐
	if (player->Getter_PlayerLife() > 0 && blockMgr->Getter_LiveNum() != 0) {//残機があるかつクリアしてないとき
		//画面外処理は各インスタンスに任せる.

		//衝突判定部
		//PlayerとBallが当たっていれば伝える
		Call_ColRectangleAndBall(player, ball);
		//BlockとBallの当たり判定
		for (int i = 0; i < Define::BLOCK_NUM; i++) {
			//生きているなら
			if (blockMgr->Getter_LiveBlock(i) != nullptr) {//nullptr便利だけどこんなことやっていい?
				if (Call_ColRectangleAndBall(blockMgr->Getter_LiveBlock(i), ball)) {//当たったら
					blockMgr->SetBlockFlag_Live(i, false);
				}
			}
		}

		blockMgr->Update();
		//ballが待ち状態なら動けない
		if (!ball->CheckFlag((int)Ball::fBall::_wait)) {
			player->Update();
		}
		if (ball->CheckFlag((int)Ball::fBall::_move)) {
			ball->Update();
		}
		else {//ballがplayerに追従するとき
			ball->Update(player->GetterPosX() + player->GetterWidth() / 2, player->GetterPosY() - (ball->GetterR()));
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) != 0) {

			}

		}

		//ボールが下に落ちた時
		if (ball->CheckFlag((int)Ball::fBall::_out)) {
			ball->Finalize();
			//インスタンスへのポインタを解放
			ball.reset();
			player->CallDecLife();

			//新しいポインタを代入
			ball = std::make_shared<Ball>(player->GetterPosX() + player->GetterWidth() / 2, player->GetterPosY() - Define::BALL_RADIUS);
			ball->Initialize();
		}
	}
	else if(player->Getter_PlayerLife() <= 0){//残機が無くなったら
		player->SetPlayerFlag_Death(true);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Over", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Continue is Space", Define::WHITE);

		//スペースが押されたらコンティニュー
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//playerの終了と初期化処理
			player->Finalize();
			player.reset();
			player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
			player->Initialize();
		}
	}
	else if (blockMgr->Getter_LiveNum() <= 0) {//blockを全て消せたら
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Clear!", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Restart is Spece", Define::WHITE);

		//スペースが押されたらリスタート
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//playerの終了と初期化処理
			player->Finalize();
			player.reset();
			player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
			player->Initialize();

			ball->Finalize();
			ball.reset();
			ball = std::make_shared<Ball>(player->GetterPosX() + player->GetterWidth() / 2, player->GetterPosY() - Define::BALL_RADIUS);
			ball->Initialize();

			blockMgr->Finalize();
			blockMgr.reset();
			blockMgr = std::make_shared<BlockMgr>();
			blockMgr->Initialize();
		}
	}

	
}

void GameMgr::Draw() const {
	if (!player->CheckFlag((int)Player::fPlayer::_death)) {
		player->Draw();
		blockMgr->Draw();
		ball->Draw();
	}
	

	for (int i = 0; i < player->Getter_PlayerLife(); i++) {
		DrawString(i*15, 10, "●", Define::WHITE);
	}
}

bool GameMgr::Call_ColRectangleAndBall(std::shared_ptr<RectangleObject> rectangle, std::shared_ptr<Ball> ball) {

	//水平の壁に当たれば垂直に跳ね返る.水平優先.
	if (colMgr.ColHori_RectAndBall(*rectangle, *ball)) {
		ball->ReflectBlock_Vertical(rectangle);

		return true;
	}

	//垂直の壁に当たれば水平に跳ね返る
	if (colMgr.ColVert_RectAndBall(*rectangle, *ball)) {
		ball->ReflectBlock_Horizontal(rectangle);

		return true;
	}

	return false;
}
