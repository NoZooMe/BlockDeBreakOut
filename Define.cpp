#include "Define.h"
#include <DxLib.h>

const int Define::SCREEN_WIDTH = 1280;		//�E�B���h�E�T�C�Y��
const int Define::SCREEN_HEIGHT = 960;		//�E�B���h�E�T�C�Y�c

const float Define::PI = 3.141592654f;		//�~����

const int Define::WHITE = GetColor(255, 255, 255);
const int Define::RED = GetColor(255, 0, 0);
const int Define::GREEN = GetColor(0, 255, 0);
const int Define::BLUE = GetColor(0, 0, 255);

const int Define::NORMAL = 1;
const int Define::HARD = 2;

//Player�֘A
const int Define::PLAYER_LIFE = 5;
const int Define::PLAYER_WIDTH = SCREEN_WIDTH / 7;
const int Define::PLAYER_HEIGHT = SCREEN_HEIGHT/40;
const int Define::PLAYER_INIX = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
const int Define::PLAYER_INIY = SCREEN_HEIGHT * 5 / 6;
const int Define::PLAYER_SCREEN_HEIGHT = SCREEN_HEIGHT * 3 / 5;

//ball�֘A
const int Define::BALL_RADIUS = PLAYER_WIDTH/8;
const int Define::BALL_INIX = SCREEN_WIDTH/2;
const int Define::BALL_INIY = PLAYER_INIY - BALL_RADIUS;

//block�֘A
const int Define::BLOCK_WIDTH = PLAYER_WIDTH/2;
const int Define::BLOCK_HEIGHT = PLAYER_HEIGHT*2;
const int Define::BLOCK_ROW = 10;
const int Define::BLOCK_GAPX = 10;
const int Define::BLOCK_GAPY = 30;
const int Define::BLOCK_COLUMN = 5;
const int Define::BLOCK_NUM = BLOCK_ROW * BLOCK_COLUMN;

//bullet�֘A
const int Define::BULLET_SIZE_SMALL = BALL_RADIUS / 2;
const int Define::BULLET_SIZE_BIG = BALL_RADIUS * 3;