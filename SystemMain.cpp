#include <DxLib.h>
#include "SystemMain.h"
#include "Define.h"
#include "Looper.h"
#include "Macro.h"

bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);		//�E�B���h�E���m���A�N�e�B�u�ł����s
	SetWindowSizeChangeEnableFlag(TRUE);		//�E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
	SetOutApplicationLogValidFlag(FALSE);		//���O�o�͂��Ȃ�
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);		//�t���X�N���[�����ɏc������ێ�����
	SetWindowText("Block��BreakOut!!");		//�E�B���h�E�^�C�g����t����
	ChangeWindowMode(TRUE);		//�E�B���h�E���[�h�ɕύX
//	SetWindowSizeExtendRate(1.0);		//�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
	const int COLOR_BIT = 32;		//�F��bit���B�ʏ�32�ł������y������Ȃ�16�ɂ���
	SetGraphMode(Define::DISPLAY_WIDTH, Define::SCREEN_HEIGHT, COLOR_BIT);		//�Q�[����ʂ̉𑜓x���w�肷��
	if (DxLib_Init()) {		//DX���C�u��������������
		ERR("DxLib�̏������Ɏ��s���܂����B");
		return false;		//�ُ�I�������瑦���ɂ�߂�
	}
	SetDrawScreen(DX_SCREEN_BACK);		//����ʏ�����ݒ肷��
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