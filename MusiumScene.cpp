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

const char* MusiumScene::Music1 = "タイトル曲";
const char* MusiumScene::Music2 = "ステージ1";

const char* MusiumScene::Data1 = "ケイ";
const char* MusiumScene::Data2 = "マツリ";
const char* MusiumScene::Data3 = "古い研究日記1";

const char* MusiumScene::Unknown = "???";

MusiumScene::MusiumScene(ISceneChangedListener* impl, const Parameter& param) : AbstractScene(impl, param),
			_playingMusic(ResourceID::COUNT), _selectingData(eData::None), _nextMusic(ResourceID::COUNT){
	_status = GlobalStatusManager::getIns()->GetGlobalStatus();
	std::map<int, std::string> musiumMenu;
	if (_status._isEnterTitle) {
		musiumMenu[0] = Data1;
	}
	else {
		musiumMenu[0] = Unknown;
	}
	if (_status._isClearStage1) {
		musiumMenu[1] = Data2;
	}
	else {
		musiumMenu[1] = Unknown;
	}
	if (_status._isNoContinueStage1) {
		musiumMenu[2] = Data3;
	}
	else {
		musiumMenu[2] = Unknown;
	}
	if (_status._isEnterTitle) {
		musiumMenu[3] = Music1;
	}
	else {
		musiumMenu[3] = Unknown;
	}
	if (_status._isEnterStage1) {
		musiumMenu[4] = Music2;
	}
	else {
		musiumMenu[4] = Unknown;
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

	if (_choices->Update() == 0) {

	}
	else if (_choices->Update() == 1) {
		if (_status._isEnterTitle) {
			_selectingData = eData::Kei;
		}
		else {
			_selectingData = eData::None;
		}
	}
	else if (_choices->Update() == 2) {
		if (_status._isClearStage1) {
			_selectingData = eData::Matsuri;
		}
		else {
			_selectingData = eData::None;
		}
	}
	else if (_choices->Update() == 3) {
		if (_status._isNoContinueStage1) {
			_selectingData = eData::Data1;
		}
		else {
			_selectingData = eData::None;
		}
	}
	else if (_choices->Update() == 4) {
		if (_status._isEnterTitle) {
			_selectingData = eData::TitleMusic;
			_nextMusic = ResourceID::TitleBGM;
		}
		else {
			_selectingData = eData::None;
			_nextMusic = ResourceID::COUNT;
		}
	}
	else if (_choices->Update() == 5) {
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
		ERR("選択された項目が無効です。");
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
	DrawString(60, 30, "資料室", Define::WHITE);

	DrawBox(0, 0, 180, Define::SCREEN_HEIGHT, Define::GREEN, false);
	DrawLine(0, 50, 180, 50, Define::GREEN);
	DrawLine(180, 600, Define::DISPLAY_WIDTH, 600, Define::GREEN);

	switch (_selectingData) {
	case eData::None:
		break;
	case eData::Kei:
		DrawGraph((Define::DISPLAY_WIDTH - 180) / 2, Define::SCREEN_HEIGHT - 800, ImageManager::getIns()->getImage(toString(ResourceID::Zero)), true);
		DrawString(200, 620, "政府に反乱する組織のリーダー。", Define::WHITE);
		break;
	case eData::Matsuri:
		DrawGraph((Define::DISPLAY_WIDTH - 180) / 2, Define::SCREEN_HEIGHT - 800, ImageManager::getIns()->getImage(toString(ResourceID::First)), true);
		DrawString(200, 620, "魔法が確認されてから産まれたいわゆる\"ネイティブ\"。", Define::WHITE);
		break;
	case eData::Data1:
		break;
	case eData::TitleMusic:
		DrawString(200, 620, "タイトル曲です。ワクワクする感じが出せたらいいなぁと思います。", Define::WHITE);
		break;
	case eData::Stage1Music:
		DrawString(200, 620, "ステージ1の曲です。元気が良すぎる気もします。", Define::WHITE);
		break;
	default:
		ERR("選択したデータが無効です");
	}

}

