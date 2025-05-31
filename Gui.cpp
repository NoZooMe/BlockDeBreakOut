#include "Gui.h"
#include <DxLib.h>

void Gui::Initialize() {

}

void Gui::Finalize() {

}

void Gui::Update(const PlayerStatus& _status) {
	_drawnStatus = _status;
}

void Gui::Draw() const {
	DrawBox(Define::SCREEN_WIDTH, 0, Define::DISPLAY_WIDTH, Define::SCREEN_HEIGHT, Define::BLUE, false);
	DrawString(Define::SCREEN_WIDTH + (100), Define::SCREEN_HEIGHT/2, "Life", Define::WHITE);
	for (int i = 0; i < _drawnStatus._life; ++i) {
		DrawString(Define::SCREEN_WIDTH + (100) + i * 15, Define::SCREEN_HEIGHT/2 + 20, "��", Define::WHITE);
	}
	DrawString(Define::SCREEN_WIDTH + (100), Define::SCREEN_HEIGHT/2 + 45, "Bomb", Define::WHITE);
	for (int i = 0; i < _drawnStatus._bomb; ++i) {
		DrawString(Define::SCREEN_WIDTH + (100) + i * 15, Define::SCREEN_HEIGHT/2 + 70, "��", Define::WHITE);
	}

	DrawString(Define::SCREEN_WIDTH + (100), Define::SCREEN_HEIGHT / 2 + 90, "Score", Define::WHITE);
	DrawFormatString(Define::SCREEN_WIDTH + (100), Define::SCREEN_HEIGHT / 2 + 110, Define::WHITE, "%d", _drawnStatus);
}