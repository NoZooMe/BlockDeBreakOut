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

const char* MusiumScene::Data0 = "2*42/05/21";
const char* MusiumScene::Data1 = "ケイ";
const char* MusiumScene::Data2 = "マツリ";
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
	DrawLine(180, 800, Define::DISPLAY_WIDTH, 800, Define::GREEN);

	switch (_selectingData) {
	case eData::None:
		break;
	case eData::Data0:
		DrawString(200, 820, "新しい新聞記事のようだ。見出しにはこう書かれている。\n"
				"【号外 政府反乱軍\"クラテミス\"のリーダー、ケイ捕まる!!】", Define::WHITE);
		break;
	case eData::Kei:
		DrawGraph((Define::DISPLAY_WIDTH - 180) / 2, 0, ImageManager::getIns()->getImage(toString(ResourceID::Kei1)), true);
		DrawString(200, 820, "政府に属さない組織\"クラテミス\"のリーダー。魔法が確認される前の人類であり、独学で魔法を習得した。\n"
								"元々は有能な科学者であり、クラテミスを作る前はEUIという研究機関に若いながらも所属していた。\n"
								"専攻は、完全なランダム性を実現できるのではと思われていた魔子という粒子の研究。", Define::WHITE);
		break;
	case eData::Matsuri:
		DrawGraph((Define::DISPLAY_WIDTH - 180) / 2, 0, ImageManager::getIns()->getImage(toString(ResourceID::Nagisa1)), true);
		DrawString(200, 820, "魔法が確認されてから産まれたいわゆる\"ネイティブ\"。\n"
								"魔法を制御しようとしている政府では、魔法への適正が高いネイティブは重宝されているようで、\n"
								"彼女は若いながらも政府へ反乱する魔法使いを閉じ込める監獄の看守を任されている。\n"
								"空間を歪める魔法を用いることが出来る。", Define::WHITE);
		break;
	case eData::Data1:
		DrawString(200, 820, "古い新聞記事のようだ。見出しにはこう書かれている。\n"
			"【広がる魔法の脅威。打つ手なしとEUIは発表。】\n"
			"ボロボロの紙面には、黒いパラボラアンテナの写真が載せられている。", Define::WHITE);
		break;
	case eData::TitleMusic:
		DrawString(200, 820, "タイトル曲です。ワクワクする感じが出せたらいいなぁと思います。", Define::WHITE);
		break;
	case eData::Stage1Music:
		DrawString(200, 820, "ステージ1の曲です。元気が良すぎる気もします。", Define::WHITE);
		break;
	default:
		ERR("選択したデータが無効です");
	}

}

