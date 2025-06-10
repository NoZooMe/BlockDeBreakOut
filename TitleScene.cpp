#include "TitleScene.h"
#include "Define.h"
#include "Keyboard.h"
#include "GameScene.h"
#include "ResourceID.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "GlobalStatusManager.h"
#include <DxLib.h>
#include <map>

using namespace std;

const char* TitleScene::TitleMenu1 = "�Q�[��";
const char* TitleScene::TitleMenu2 = "�������";
const char* TitleScene::TitleMenu3 = "������";
const char* TitleScene::TitleMenu4 = "�ݒ�";
const char* TitleScene::TitleMenu5 = "�I��";

TitleScene::TitleScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), _alpha(0), _fadeInTime(900), 
	_frameCnt(0), _isInputEnabled(false), _isTutorial(false){
	//�����͊m���ɂ��悤������
	map<int, string> titleMenu;
	titleMenu[0] = TitleMenu1;
	titleMenu[1] = TitleMenu2;
	titleMenu[2] = TitleMenu3;
	titleMenu[3] = TitleMenu4;
	titleMenu[4] = TitleMenu5;

	_titleMenu = make_shared<Choices>(titleMenu);
}

TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {
	SoundManager::getIns()->play(toString(ResourceID::TitleBGM), true);
	GlobalStatusManager::getIns()->SetGlobalFlag(eGlobalStatusFlag::TitleEnter, true);
}
	

void TitleScene::Finalize() {
	SoundManager::getIns()->stop(toString(ResourceID::TitleBGM));
}

void TitleScene::Update() {
	if (_isInputEnabled && !_isTutorial) {
		if (_titleMenu->Update() == 0) {

		}
		else if (_titleMenu->Update() == 1) {
			Parameter parameter;
			parameter.set(GameScene::ParameterTagLevel, Define::NORMAL);
			_implSceneChangedListener->onSceneChanged(Game, parameter, true);
			
		}
		else if (_titleMenu->Update() == 2) {
			_isTutorial = true;
		} 
		else if (_titleMenu->Update() == 3) {
			Parameter parameter;
			_implSceneChangedListener->onSceneChanged(Musium, parameter, false);

		}
		else if (_titleMenu->Update() == 4) {
			Parameter parameter;
		}
		else if (_titleMenu->Update() == 5) {
			_implSceneChangedListener->exitGame();
		}
	}
	if (_isTutorial) {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
			_isTutorial = false;
		}
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) >= 1) {
		_isInputEnabled = true;
		_alpha = 255;	//�����ɕ\������
	}

	//�t�F�[�h�C������
	if (!_isInputEnabled) {
		if (_frameCnt < _fadeInTime) {
			_alpha = 255 * _frameCnt / _fadeInTime;
		}
		else {
			_isInputEnabled = true;
			_alpha = 255;
		}
		_frameCnt++;
	}
}

void TitleScene::Draw() const {
	if (!_isTutorial) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawGraph(0, 0, ImageManager::getIns()->getImage(toString(ResourceID::Title)), false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (_isInputEnabled) {
			_titleMenu->Draw();
			DrawGraph(20, Define::SCREEN_HEIGHT - 800, ImageManager::getIns()->getImage(toString(ResourceID::Zero)), true);
		}
	}
	else {
		DrawString(200, 200, "�S�����瓦���o�����߂Ƀu���b�N������Ȃ���G�̒e�������I�@�Ƃ��������ăV���v���ȃQ�[���ł��B\n"
			"�����̃{�[���𗎂Ƃ��Ă��A�G�̒e�ɓ������Ă��_���[�W���󂯂܂��B�{�[���𓖂Ăău���b�N��S�ĕ������Ƃ��ł���΃N���A�ł��B\n"
			"�ȉ��A��������ɂȂ�܂��B\n\n"
			"���厖�ȑ���\n"
			"�\���L�[:�ړ�\nSpace�L�[:�{�[���𔭎˂��܂��B���ˎ��������Ŋp�x��ς����܂��B\n"
			"Z�L�[:�{�������Ă܂��B�{���͓G�̒e��S�ď����ăX�R�A�A�C�e���ɂ��Ă���܂��B\n"
			"��Shift�L�[:�����Ă���Ԃ͎����̕��������ɂȂ�܂��B�G�̒e��������ɂ����Ȃ�܂����{�[�����Ԃ��ɂ����Ȃ�܂�\n\n"
			"��������������g����������Ȃ�����\n"
			"��Ctrl�L�[:�����Ă���ԃ_�b�V���ł��܂��B\n"
			"X�L�[:�����̃{�[�����u���Ɏ茳�ɖ߂��܂��B���̎��A�����̗̑͂͌���܂���B\n"
			"D�L�[:�����Ă���ԁA���v���ɏ��������X���܂��B�{�[�����E�ɔ��˂����������ɕ֗��ł��B\n"
			"A�L�[:���x�͔����v���ɏ��������X���܂��B�{�[�������ɔ��˂����������ɕ֗��ł��B\n\n"
			"�u���b�N������ƃA�C�e�����o�Ă��܂��B������擾����Ɨl�X�ȉ��b�𓾂邱�Ƃ��ł��܂��B\n\n\n"
			"Esc�L�[�Ń^�C�g���ɖ߂邱�Ƃ��o���܂��B", Define::WHITE);
	}
	
}