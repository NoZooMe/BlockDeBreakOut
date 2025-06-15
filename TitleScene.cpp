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

TitleScene::TitleScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), _alpha(0), _fadeInTime(880), 
	_frameCnt(0), _isInputEnabled(false), _isTutorial(false), _isConfig(false), _postEnabled(_isInputEnabled){
	//�����͊m���ɂ��悤������
	map<int, string> titleMenu;
	titleMenu[0] = TitleMenu1;
	titleMenu[1] = TitleMenu2;
	titleMenu[2] = TitleMenu3;
	titleMenu[3] = TitleMenu4;
	titleMenu[4] = TitleMenu5;

	_titleMenu = make_shared<Choices>(titleMenu);
	_effectPipeline = make_shared<EffectPipeline>(Define::DISPLAY_WIDTH, Define::SCREEN_HEIGHT);

	_volume = GlobalStatusManager::getIns()->GetBgmVolume();
	_volumeRate = static_cast<float>(_volume) / 255.0f * 100.0f;
}

TitleScene::~TitleScene() {

}

void TitleScene::Initialize() {
	SoundManager::getIns()->play(toString(ResourceID::TitleBGM), true);
	GlobalStatusManager::getIns()->SetGlobalFlag(eGlobalStatusFlag::TitleEnter, true);
	_effectPipeline->Initialize();
}
	

void TitleScene::Finalize() {
	SoundManager::getIns()->stop(toString(ResourceID::TitleBGM));
	_effectPipeline->Finalize();
}

void TitleScene::Update() {
	_effectPipeline->Update();
	if (_isInputEnabled) {

		if (!_isTutorial && !_isConfig) {
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
				_isConfig = true;
			}
			else if (_titleMenu->Update() == 5) {
				_implSceneChangedListener->exitGame();
			}
		} else if (_isTutorial && !_isConfig) {
				if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
					_isTutorial = false;
			}
		} else if (_isConfig && !_isTutorial) {
				if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
					_isConfig = false;
			}
				if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) % 5 == 1 && _volumeRate < 100) {
					_volumeRate++;

					_volume = static_cast<float>(_volumeRate) / 100.0f * 255.0f;

					SoundManager::getIns()->set(_volume);
					SoundManager::getIns()->play(toString(ResourceID::PowerUpSE));
				}
				if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) % 5 == 1 && _volumeRate > 0) {
					_volumeRate--;

					_volume = static_cast<float>(_volumeRate) / 100.0f * 255.0f;

					SoundManager::getIns()->set(_volume);
					SoundManager::getIns()->play(toString(ResourceID::PowerUpSE));
				}

				GlobalStatusManager::getIns()->SetBgmVolume(_volume);
		}
	}
	else {
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) >= 1) {
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

		if (_postEnabled != _isInputEnabled) {
			_effectPipeline->AddWhiteFlashEffect(20);
		}
		_postEnabled = _isInputEnabled;
	}

}

void TitleScene::Draw() const {
	if ((!_isTutorial) && (!_isConfig)) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawGraph(0, 0, ImageManager::getIns()->getImage(toString(ResourceID::Title)), false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (_isInputEnabled) {
			_effectPipeline->Draw([&] {_titleMenu->Draw(),
				DrawGraph(20, Define::SCREEN_HEIGHT - 800, ImageManager::getIns()->getImage(toString(ResourceID::Zero)), true), 
				DrawString(Define::DISPLAY_WIDTH/2 - 100, Define::SCREEN_HEIGHT/2 + 200, "Press Enter", Define::WHITE); });
			
		}
	}
	else if(_isTutorial){
		DrawString(200, 200, "�S�����瓦���o�����߂Ƀu���b�N������Ȃ���G�̒e�������I�@�Ƃ��������ăV���v���ȃQ�[���ł��B\n"
			"�����̃{�[���𗎂Ƃ��Ă��A�G�̒e�ɓ������Ă��_���[�W���󂯂܂��B�{�[���𓖂Ăău���b�N��S�ĕ������Ƃ��ł���΃N���A�ł��B\n"
			"�ȉ��A��������ɂȂ�܂��B\n\n"
			"���厖�ȑ���\n"
			"�\���L�[:�ړ�\nSpace�L�[:�{�[���𔭎˂��܂��B���ˎ��������Ŋp�x��ς����܂��B\n"
			"�܂��A�{�[���������Ă��鎞��Space�L�[�������ƃ{�[�����茳�ɖ߂����Ƃ��o���܂��B���̂Ƃ��̗͂͌���܂���B\n"
			"Z�L�[:�{�������Ă܂��B�{�������ƁA�G�̒e���͑S�ăX�R�A�A�C�e���ɕω����܂��B\n"
			"��Shift�L�[:�����Ă���Ԃ͎����̕��������ɂȂ�܂��B�G�̒e��������ɂ����Ȃ�܂����{�[�����Ԃ��ɂ����Ȃ�܂��B\n\n"
			"��������������g����������Ȃ�����\n"
			"��Ctrl�L�[:�����Ă���ԃ_�b�V���ł��܂��B\n"
			"D�L�[:�����Ă���ԁA���v���ɏ��������X���܂��B�{�[�����E�ɔ��˂����������ɕ֗��ł��B\n"
			"A�L�[:���x�͔����v���ɏ��������X���܂��B�{�[�������ɔ��˂����������ɕ֗��ł��B\n\n"
			"�u���b�N������ƃA�C�e�����o�Ă��܂��B������擾����Ɨl�X�ȉ��b�𓾂邱�Ƃ��ł��܂��B\n\n\n"
			"Esc�L�[�Ń^�C�g���ɖ߂邱�Ƃ��o���܂��B", Define::WHITE);
	}
	else if (_isConfig) {
		DrawString(200, 200, "�����Ń{�����[����ݒ肵�܂��B", Define::WHITE);
		DrawFormatString(200, 215, Define::WHITE, "%d", _volumeRate);
		DrawString(200, 230, "ESC�L�[�Ń^�C�g���ɖ߂邱�Ƃ��o���܂��B", Define::WHITE);

	}
	
}