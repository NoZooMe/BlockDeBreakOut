#pragma once
class Define final
{
public:
	const static int SCREEN_WIDTH;		//ウィンドウサイズ横
	const static int SCREEN_HEIGHT;		//ウィンドウサイズ縦

	const static float PI;		//円周率

	const static int WHITE;
	const static int RED;
	const static int GREEN;
	const static int BLUE;

	const static int NORMAL;
	const static int HARD;

	//Player関連
	const static int PLAYER_LIFE;
	const static int PLAYER_WIDTH;
	const static int PLAYER_HEIGHT;
	const static int PLAYER_INIX;
	const static int PLAYER_INIY;
	const static int PLAYER_SCREEN_HEIGHT;
	const static int PLAYER_IMAGESIZEX;
	const static int PLAYER_IMAGESIZEY;

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
};

