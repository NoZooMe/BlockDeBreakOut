#include "Gui.h"
#include "ImageManager.h"
#include "ResourceID.h"
#include "BlockMgr.h"
#include <DxLib.h>


void Gui::Initialize() {
	_isPhase1 = true;
	_isPhase2 = false;
	_isPhase3 = false;
	_liveNum = Define::BLOCK_NUM;
}

void Gui::Finalize() {

}

void Gui::Update(const PlayerStatus& status, const int liveBlockNum) {
	_drawnStatus = status;

	_liveNum = liveBlockNum;

	if (_liveNum <= Define::SPELL_BLOCK_NUM && _liveNum > 0) {
		_isPhase1 = false;
		_isPhase2 = true;
		_isPhase3 = false;
	}
	else if (_liveNum <= 0) {
		_isPhase1 = false;
		_isPhase2 = false;
		_isPhase3 = true;
	}
	else {
		_isPhase1 = true;
		_isPhase2 = false;
		_isPhase3 = false;
	}
}

void Gui::Draw() const {
	//枠
	DrawBox(Define::SCREEN_WIDTH, 0, Define::DISPLAY_WIDTH, Define::SCREEN_HEIGHT, Define::BLUE, false);
	//敵の名前
	DrawString(Define::UI_X, Define::ENEMY_NAME_Y, "VS マツリ", Define::WHITE);
	//敵の画像
	DrawExtendGraph(Define::SCREEN_WIDTH, Define::ENEMY_ILLUST_Y, Define::SCREEN_WIDTH + 283, 430, ImageManager::getIns()->getImage(toString(ResourceID::First)), true);

	//敵のセリフ
	if (_isPhase1) {
		DrawString(Define::SCREEN_WIDTH+5, Define::ENEMY_DIALOGUE_Y, "さくっと倒させてもらいますよ。", Define::WHITE);
	}
	if (_isPhase2) {
		DrawString(Define::SCREEN_WIDTH+5, Define::ENEMY_DIALOGUE_Y, "まずいですね……。\n少々手荒になるが魔法を使うか……。", Define::WHITE);
	}
	if (_isPhase3) {
		DrawString(Define::SCREEN_WIDTH+5, Define::ENEMY_DIALOGUE_Y, "まさかっ！　逃げられるなんて！？", Define::WHITE);
	}

	//プレイヤーのライフ
	DrawString(Define::UI_X, Define::PLAYER_LIFE_Y, "Life", Define::WHITE);
	for (int i = 0; i < _drawnStatus._life; ++i) {
		DrawString(Define::UI_X + i * 15, Define::PLAYER_LIFE_Y + 20, "●", Define::WHITE);
	}
	//プレイヤーのボム
	DrawString(Define::UI_X, Define::PLAYER_BOMB_Y, "Bomb", Define::WHITE);
	for (int i = 0; i < _drawnStatus._bomb; ++i) {
		DrawString(Define::UI_X + i * 15, Define::PLAYER_BOMB_Y + 25, "★", Define::WHITE);
	}
	//プレイヤーのスコア
	DrawString(Define::UI_X, Define::PLAYER_SCORE_Y, "Score", Define::WHITE);
	DrawFormatString(Define::UI_X, Define::PLAYER_SCORE_Y + 20, Define::WHITE, "%d", _drawnStatus._score);
	DrawString(Define::UI_X, Define::PLAYER_SCORE_Y + 40, "HighScore", Define::WHITE);
	DrawFormatString(Define::UI_X, Define::PLAYER_SCORE_Y + 60, Define::WHITE, "%d", _drawnStatus._highScore);

	//ゲームオーバー
	if (_drawnStatus._life <= 0) {
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Over", Define::WHITE);
		if (_drawnStatus._continue > 0) {
			DrawFormatString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, Define::WHITE, "Continue is Space. Credit:%d", _drawnStatus._continue);
		}
		else {
			DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, "Press Space to Return Title", Define::WHITE);
		}
	}

	//ゲームクリア
	if (_liveNum == 0) {
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2, "Game Clear!", Define::WHITE);
		DrawFormatString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 15, Define::WHITE, "Your final socre is %d", _drawnStatus._score);
		DrawString(Define::SCREEN_WIDTH / 2, Define::SCREEN_HEIGHT / 2 + 30, " Press Spece", Define::WHITE);
	}

}