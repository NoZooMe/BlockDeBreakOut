#include "GameMgr.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include <DxLib.h>

using namespace std;

GameMgr::GameMgr() : _player(make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY)), _ball(make_shared<Ball>(Define::BALL_INIX, Define::BALL_INIY)){
	
}

void GameMgr::Initialize() {
	_player->Initialize();
	_ball->Initialize();
}

void GameMgr::Finalize() {
	_player->Finalize();
	_ball->Finalize();

}

void GameMgr::Update(shared_ptr<BlockMgr> blockMgr, shared_ptr<BulletMgr> bulletMgr) {

	//残機があるときとないときで分岐
	if (_player->Getter_PlayerLife() > 0 && blockMgr->Getter_LiveNum() != 0) {//残機があるかつクリアしてないとき
		//画面外処理は各インスタンスに任せる.

		//衝突判定部
		//PlayerとBallが当たっていれば伝える
		Call_ColRectangleAndBall(_player, _ball);
		
		//BlockとBallの当たり判定
		for (int i = 0; i < Define::BLOCK_NUM; i++) {
			//生きているなら
			if (blockMgr->Getter_LiveBlock(i) != nullptr) {//nullptr便利だけどこんなことやっていい?
				if (Call_ColRectangleAndBall(blockMgr->Getter_LiveBlock(i), _ball)) {//当たったら
					blockMgr->SetBlockFlag_Live(i, false);
				}
			}
		}
		
		//Playerにも待ち状態を作ってこちらがやるのはflagのONのみにする。
		//ballが待ち状態なら動けない
		if (!_ball->CheckFlag((int)Ball::fBall::_wait)) {
			_player->Update();
		}
		if (_ball->CheckFlag((int)Ball::fBall::_move)) {
			_ball->Update();
		}
		else {//ballがplayerに追従するとき
			_ball->Update(_player->GetterPosX() + _player->GetterWidth() / 2, _player->GetterPosY() - (_ball->GetterR()));
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) != 0) {

			}

		}

		//落ちたかどうかはGameMgrが判定。boolで返しその後の処理はStageSceneに任せる。
		//ボールが下に落ちた時
		if (_ball->CheckFlag((int)Ball::fBall::_out)) {
			_ball->Finalize();
			//インスタンスへのポインタを解放
			_ball.reset();
			_player->CallDecLife();

			//新しいポインタを代入
			_ball = std::make_shared<Ball>(_player->GetterPosX() + _player->GetterWidth() / 2, _player->GetterPosY() - Define::BALL_RADIUS);
			_ball->Initialize();
		}
	}
	else if(_player->Getter_PlayerLife() <= 0){//残機が無くなったら
		_player->SetPlayerFlag_Death(true);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Over", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Continue is Space", Define::WHITE);

		//スペースが押されたらコンティニュー
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
			//playerの終了と初期化処理
			_player->Finalize();
			_player.reset();
			_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
			_player->Initialize();
		}
	}
	else if (blockMgr->Getter_LiveNum() <= 0) {//blockを全て消せたら
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Clear!", Define::WHITE);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Restart is Spece", Define::WHITE);

		////スペースが押されたらリスタート
		// ここはStageSceneでやる
		//if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
		//	//playerの終了と初期化処理
		//	_player->Finalize();
		//	_player.reset();
		//	_player = std::make_shared<Player>(Define::PLAYER_INIX, Define::PLAYER_INIY);
		//	_player->Initialize();

		//	_ball->Finalize();
		//	_ball.reset();
		//	_ball = std::make_shared<Ball>(_player->GetterPosX() + _player->GetterWidth() / 2, _player->GetterPosY() - Define::BALL_RADIUS);
		//	_ball->Initialize();

		//	blockMgr->Finalize();
		//	blockMgr.reset();
		//	blockMgr = std::make_shared<BlockMgr>();
		//	blockMgr->Initialize();
		//}
	}

	
}

void GameMgr::Draw() const {
	if (!_player->CheckFlag((int)Player::fPlayer::_death)) {
		_player->Draw();
		_ball->Draw();
	}
	

	for (int i = 0; i < _player->Getter_PlayerLife(); i++) {
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

Vector2<float> GameMgr::GetterPlayerPosition() const {
	return _player->GetterPosition();
}