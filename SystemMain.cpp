#include <DxLib.h>
#include "SystemMain.h"
#include "Define.h"
#include "Looper.h"
#include "Macro.h"

bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);		//ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(TRUE);		//ウィンドウサイズを自由に変更できるようにする
	SetOutApplicationLogValidFlag(FALSE);		//ログ出力しない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);		//フルスクリーン時に縦横比を維持する
	SetWindowText("BlockでBreakOut!!");		//ウィンドウタイトルを付ける
	ChangeWindowMode(TRUE);		//ウィンドウモードに変更
//	SetWindowSizeExtendRate(1.0);		//ウィンドウサイズを変更したい時はここに倍率を指定する
	const int COLOR_BIT = 32;		//色のbit数。通常32でいいが軽くするなら16にする
	SetGraphMode(Define::DISPLAY_WIDTH, Define::SCREEN_HEIGHT, COLOR_BIT);		//ゲーム画面の解像度を指定する
	if (DxLib_Init()) {		//DXライブラリ初期化処理
		ERR("DxLibの初期化に失敗しました。");
		return false;		//異常終了したら即座にやめる
	}
	SetDrawScreen(DX_SCREEN_BACK);		//裏画面処理を設定する
	return true;
}

void SystemMain::finalize() const
{
	DxLib_End();
}

void SystemMain::main() const
{
	Looper looper;
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!looper.loop()) {
			break;
		}
	}
}