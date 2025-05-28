#include "Define.h"
#include <DxLib.h>

const int Define::SCREEN_WIDTH = 1000;		//ウィンドウサイズ横
const int Define::SCREEN_HEIGHT = 960;		//ウィンドウサイズ縦

const int Define::DISPLAY_WIDTH = 1280;

const float Define::PI = 3.141592654f;		//円周率

const int Define::WHITE = GetColor(255, 255, 255);
const int Define::RED = GetColor(255, 0, 0);
const int Define::GREEN = GetColor(0, 255, 0);
const int Define::BLUE = GetColor(0, 0, 255);

const int Define::NORMAL = 1;
const int Define::HARD = 2;

//Player関連
const int Define::PLAYER_LIFE = 5;
const int Define::PLAYER_BOMB = 5;
const int Define::PLAYER_WIDTH = 160;
const int Define::PLAYER_HEIGHT = 16;
const int Define::PLAYER_INIX = SCREEN_WIDTH / 2;
const int Define::PLAYER_INIY = SCREEN_HEIGHT * 5 / 6;
const int Define::PLAYER_SCREEN_HEIGHT = SCREEN_HEIGHT * 3 / 5;

//ball関連
const int Define::BALL_RADIUS = 20;
const int Define::BALL_INIX = SCREEN_WIDTH/2;
const int Define::BALL_INIY = PLAYER_INIY - (BALL_RADIUS+PLAYER_HEIGHT/2);

//block関連
const int Define::BLOCK_WIDTH = SCREEN_WIDTH/10;
const int Define::BLOCK_HEIGHT = 60;
const int Define::BLOCK_ROW = 10;
const int Define::BLOCK_GAPX = 0;
const int Define::BLOCK_GAPY = 50;
const int Define::BLOCK_COLUMN = 3;
const int Define::BLOCK_NUM = BLOCK_ROW * BLOCK_COLUMN;

//bullet関連
const int Define::BULLET_SIZE_SMALL = 8;
const int Define::BULLET_SIZE_MIDIUM = 20;
const int Define::BULLET_SIZE_BIG = BALL_RADIUS * 3;