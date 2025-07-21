#include "MusiumScene.h"
#include "GlobalStatusManager.h"
#include "Keyboard.h"
#include "ISceneChangedListener.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Define.h"
#include "Macro.h"
#include <DxLib.h>
#include <string>
#include <map>

const char* MusiumScene::Music1 = "�^�C�g����";
const char* MusiumScene::Music2 = "�X�e�[�W1";

const char* MusiumScene::Data0 = "2*42/05/21";
const char* MusiumScene::Data1 = "�P�C";
const char* MusiumScene::Data2 = "�}�c��";
const char* MusiumScene::Data3 = "2*27/11/02";

const char* MusiumScene::Unknown = "???";

MusiumScene::MusiumScene(ISceneChangedListener* impl, const Parameter& param) : AbstractScene(impl, param),
			_playingMusic(ResourceID::COUNT), _selectingData(eData::None), _nextMusic(ResourceID::COUNT){
	_status = GlobalStatusManager::getIns()->GetGlobalStatus();
	std::map<int, std::string> musiumMenu;

	if (_status._isEnterTitle) {
		musiumMenu[0] = Data0;
		musiumMenu[1] = Data1;
	}
	else {
		musiumMenu[0] = Unknown;
		musiumMenu[1] = Unknown;
	}
	if (_status._isClearStage1) {
		musiumMenu[2] = Data2;
	}
	else {
		musiumMenu[2] = Unknown;
	}
	if (_status._isNoContinueStage1) {
		musiumMenu[3] = Data3;
	}
	else {
		musiumMenu[3] = Unknown;
	}
	if (_status._isEnterTitle) {
		musiumMenu[4] = Music1;
	}
	else {
		musiumMenu[4] = Unknown;
	}
	if (_status._isEnterStage1) {
		musiumMenu[5] = Music2;
	}
	else {
		musiumMenu[5] = Unknown;
	}

	_choices = std::make_shared<Choices>(musiumMenu, 20, 70, true);
}

void MusiumScene::Initialize() {
	
}

void MusiumScene::Finalize() {
	if (!(_playingMusic == ResourceID::COUNT)) {
		SoundManager::getIns()->stop(toString(_playingMusic));
	}
}

void MusiumScene::Update() {
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
		Parameter param;
		_implSceneChangedListener->onSceneChanged(eScene::Title, param, false);
	}

	int selected = _choices->Update();

	if (selected == 0) {

	}
	else if (selected == 1) {
		if (_status._isEnterTitle) {
			_selectingData = eData::Data0;
		}
		else {
			_selectingData = eData::None;
		}
	}
	else if (selected == 2) {
		if (_status._isEnterTitle) {
			_selectingData = eData::Kei;
		}
		else {
			_selectingData = eData::None;
		}
	}
	else if (selected == 3) {
		if (_status._isClearStage1) {
			_selectingData = eData::Matsuri;
		}
		else {
			_selectingData = eData::None;
		}
	}
	else if (selected == 4) {
		if (_status._isNoContinueStage1) {
			_selectingData = eData::Data1;
		}
		else {
			_selectingData = eData::None;
		}
	}
	else if (selected == 5) {
		if (_status._isEnterTitle) {
			_selectingData = eData::TitleMusic;
			_nextMusic = ResourceID::TitleBGM;
		}
		else {
			_selectingData = eData::None;
			_nextMusic = ResourceID::COUNT;
		}
	}
	else if (selected == 6) {
		if (_status._isEnterStage1) {
			_selectingData = eData::Stage1Music;
			_nextMusic = ResourceID::Stage1;
		}
		else {
			_selectingData = eData::None;
			_nextMusic = ResourceID::COUNT;
		}
	}
	else {
		ERR("�I�����ꂽ���ڂ������ł��B");
	}

	if (_nextMusic != _playingMusic) {
		if (!(_playingMusic == ResourceID::COUNT)) {
			SoundManager::getIns()->stop(toString(_playingMusic));
		}
		_playingMusic = _nextMusic;
		if (!(_playingMusic == ResourceID::COUNT)) {
			SoundManager::getIns()->play(toString(_playingMusic));
		}
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1) {
		_nextMusic = ResourceID::COUNT;
	}
}

void MusiumScene::Draw() const {
	_choices->Draw();
	DrawString(60, 30, "������", Define::WHITE);

	DrawBox(0, 0, 180, Define::SCREEN_HEIGHT, Define::GREEN, false);
	DrawLine(0, 50, 180, 50, Define::GREEN);
	DrawLine(180, 800, Define::DISPLAY_WIDTH, 800, Define::GREEN);

	switch (_selectingData) {
	case eData::None:
		break;
	case eData::Data0:
		DrawString(200, 820, "�V�����V���L���̂悤���B���o���ɂ͂���������Ă���B\n"
				"�y���O ���{�����R\"�N���e�~�X\"�̃��[�_�[�A�P�C�߂܂�!!�z", Define::WHITE);
		break;
	case eData::Kei:
		DrawGraph((Define::DISPLAY_WIDTH - 180) / 2, 0, ImageManager::getIns()->getImage(toString(ResourceID::Kei1)), true);
		DrawString(200, 820, "���{�ɑ����Ȃ��g�D\"�N���e�~�X\"�̃��[�_�[�B���@���m�F�����O�̐l�ނł���A�Ɗw�Ŗ��@���K�������B\n"
								"���X�͗L�\�ȉȊw�҂ł���A�N���e�~�X�����O��EUI�Ƃ��������@�ւɎႢ�Ȃ�����������Ă����B\n"
								"��U�́A���S�ȃ����_�����������ł���̂ł͂Ǝv���Ă������q�Ƃ������q�̌����B", Define::WHITE);
		break;
	case eData::Matsuri:
		DrawGraph((Define::DISPLAY_WIDTH - 180) / 2, 0, ImageManager::getIns()->getImage(toString(ResourceID::Nagisa1)), true);
		DrawString(200, 820, "���@���m�F����Ă���Y�܂ꂽ������\"�l�C�e�B�u\"�B\n"
								"���@�𐧌䂵�悤�Ƃ��Ă��鐭�{�ł́A���@�ւ̓K���������l�C�e�B�u�͏d�󂳂�Ă���悤�ŁA\n"
								"�ޏ��͎Ⴂ�Ȃ�������{�֔������閂�@�g��������߂�č��̊Ŏ��C����Ă���B\n"
								"��Ԃ�c�߂閂�@��p���邱�Ƃ��o����B", Define::WHITE);
		break;
	case eData::Data1:
		DrawString(200, 820, "�Â��V���L���̂悤���B���o���ɂ͂���������Ă���B\n"
			"�y�L���閂�@�̋��ЁB�ł�Ȃ���EUI�͔��\�B�z\n"
			"�{���{���̎��ʂɂ́A�����p���{���A���e�i�̎ʐ^���ڂ����Ă���B", Define::WHITE);
		break;
	case eData::TitleMusic:
		DrawString(200, 820, "�^�C�g���Ȃł��B���N���N���銴�����o�����炢���Ȃ��Ǝv���܂��B", Define::WHITE);
		break;
	case eData::Stage1Music:
		DrawString(200, 820, "�X�e�[�W1�̋Ȃł��B���C���ǂ�����C�����܂��B", Define::WHITE);
		break;
	default:
		ERR("�I�������f�[�^�������ł�");
	}

}

