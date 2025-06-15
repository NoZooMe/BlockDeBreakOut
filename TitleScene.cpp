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

const char* TitleScene::TitleMenu1 = "ゲーム";
const char* TitleScene::TitleMenu2 = "操作説明";
const char* TitleScene::TitleMenu3 = "資料室";
const char* TitleScene::TitleMenu4 = "設定";
const char* TitleScene::TitleMenu5 = "終了";

TitleScene::TitleScene(ISceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter), _alpha(0), _fadeInTime(880), 
	_frameCnt(0), _isInputEnabled(false), _isTutorial(false), _isConfig(false), _postEnabled(_isInputEnabled){
	//ここは確実にやりようがある
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
			_alpha = 255;	//即座に表示する
		}

		//フェードイン処理
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
		DrawString(200, 200, "牢獄から逃げ出すためにブロックを崩しながら敵の弾を避けろ！　という至ってシンプルなゲームです。\n"
			"自分のボールを落としても、敵の弾に当たってもダメージを受けます。ボールを当ててブロックを全て崩すことができればクリアです。\n"
			"以下、操作説明になります。\n\n"
			"○大事な操作\n"
			"十字キー:移動\nSpaceキー:ボールを発射します。発射時長押しで角度を変えられます。\n"
			"また、ボールが動いている時にSpaceキーを押すとボールを手元に戻すことが出来ます。このとき体力は減りません。\n"
			"Zキー:ボムを撃てます。ボムを撃つと、敵の弾幕は全てスコアアイテムに変化します。\n"
			"左Shiftキー:押している間は自分の幅が半分になります。敵の弾も当たりにくくなりますがボールも返しにくくなります。\n\n"
			"○もしかしたら使うかもしれない操作\n"
			"左Ctrlキー:押している間ダッシュできます。\n"
			"Dキー:押している間、時計回りに少しだけ傾きます。ボールを右に反射させたい時に便利です。\n"
			"Aキー:今度は反時計回りに少しだけ傾きます。ボールを左に反射させたい時に便利です。\n\n"
			"ブロックを崩すとアイテムが出てきます。これを取得すると様々な恩恵を得ることができます。\n\n\n"
			"Escキーでタイトルに戻ることが出来ます。", Define::WHITE);
	}
	else if (_isConfig) {
		DrawString(200, 200, "←→でボリュームを設定します。", Define::WHITE);
		DrawFormatString(200, 215, Define::WHITE, "%d", _volumeRate);
		DrawString(200, 230, "ESCキーでタイトルに戻ることが出来ます。", Define::WHITE);

	}
	
}