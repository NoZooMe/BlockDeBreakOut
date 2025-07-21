#pragma once
#include "Vector2.h"

class Define final
{
public:
	const static float SCREEN_WIDTH;		//ゲーム画面サイズ横
	const static float SCREEN_HEIGHT;		//ウィンドウサイズ縦

	const static float DISPLAY_WIDTH;		//ウィンドウサイズ横

	const static float PI;		//円周率

	const static int WHITE;
	const static int RED;
	const static int GREEN;
	const static int BLUE;

	const static int NORMAL;
	const static int HARD;

	//Player関連
	const static int PLAYER_LIFE;
	const static int PLAYER_BOMB;
	const static int PLAYER_SPEED;
	const static float PLAYER_WIDTH;
	const static float PLAYER_HEIGHT;
	const static float PLAYER_INIX;
	const static float PLAYER_INIY;
	const static float PLAYER_SCREEN_HEIGHT;
	const static float PLAYER_IMAGESIZEX;
	const static float PLAYER_IMAGESIZEY;
	const static int PLAYER_BOMBTIME;
	const static int PLAYER_LIFESCORE;
	const static int PLAYER_CONTINUE;

	//ball関連
	const static int BALL_RADIUS;
	const static int BALL_INIX;
	const static int BALL_INIY;

	//block関連
	const static int BLOCK_WIDTH;
	const static int BLOCK_HEIGHT;
	const static int BLOCK_ROW;
	const static int BLOCK_GAPX;
	const static int BLOCK_GAPY;
	const static int BLOCK_COLUMN;
	const static int BLOCK_NUM;

	//bullet関連
	const static int BULLET_SIZE_SMALL;
	const static int BULLET_SIZE_MIDIUM;
	const static int BULLET_SIZE_BIG;

	//item関連
	const static Vector2<float> ITEM_SPEED;
	const static int ITEM_WIDTH;
	const static int ITEM_HEIGHT;
	const static int ITEM_POWER_TIME;
	const static int ITEM_FLOATING_TIME;
	const static int ITEM_SCORE_VALUE;

	//UI関連
	const static int UI_X;
	const static int ENEMY_NAME_Y;
	const static int ENEMY_ILLUST_Y;
	const static int ENEMY_DIALOGUE_Y;
	const static int PLAYER_LIFE_Y;
	const static int PLAYER_BOMB_Y;
	const static int PLAYER_SCORE_Y;

	//Stage1関連
	const static int SPELL_BLOCK_NUM;
	const static int STAGE1_CNT;
};

