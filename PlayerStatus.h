#pragma once
#include "Define.h"

struct PlayerStatus {
	int _score = 0;
	int _highScore = 0;
	int _life = Define::PLAYER_LIFE;
	int _bomb = Define::PLAYER_BOMB;
	int _continue = Define::PLAYER_CONTINUE;
};