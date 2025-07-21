#include "Looper.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "MusiumScene.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "ResourceLoader.h"
#include "ResourceID.h"
#include "GlobalStatusManager.h"
#include "SavedataUtils.h"
#include "Keyboard.h"
#include "Macro.h"
#include <DxLib.h>

Looper::Looper() : _exitGame(false)
{
	_keyboard = _keyboard->getIns();
	
	GlobalStatus saveData = SavedataUtils::LoadBinary();
	GlobalStatusManager::getIns()->SetGlobalStatus(saveData);

	//json����resource�p�X��S�ă��[�h
	ResourceLoader::getIns()->loadFromJson("resources/resources.json");

	ImageManager::getIns()->load(toString(ResourceID::Player), ResourceLoader::getIns()->getImagePath(toString(ResourceID::Player)));
	ImageManager::getIns()->load(toString(ResourceID::Title), ResourceLoader::getIns()->getImagePath(toString(ResourceID::Title)));
	ImageManager::getIns()->load(toString(ResourceID::Nagisa1), ResourceLoader::getIns()->getImagePath(toString(ResourceID::Nagisa1)));
	ImageManager::getIns()->load(toString(ResourceID::Kei1), ResourceLoader::getIns()->getImagePath(toString(ResourceID::Kei1)));

	SoundManager::getIns()->load(toString(ResourceID::BreakBlockSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::BreakBlockSE)));
	SoundManager::getIns()->load(toString(ResourceID::OpenMenuSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::OpenMenuSE)));
	SoundManager::getIns()->load(toString(ResourceID::SelectMenuSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::SelectMenuSE)));
	SoundManager::getIns()->load(toString(ResourceID::ShotBulletSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::ShotBulletSE)));
	SoundManager::getIns()->load(toString(ResourceID::DamageSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::DamageSE)));
	SoundManager::getIns()->load(toString(ResourceID::ReflectSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::ReflectSE)));
	SoundManager::getIns()->load(toString(ResourceID::BombSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::BombSE)));
	SoundManager::getIns()->load(toString(ResourceID::PowerUpSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::PowerUpSE)));
	SoundManager::getIns()->load(toString(ResourceID::ScoreUpSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::ScoreUpSE)));
	SoundManager::getIns()->load(toString(ResourceID::EnemyAtackSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::EnemyAtackSE)));
	SoundManager::getIns()->load(toString(ResourceID::LifeUpSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::LifeUpSE)));
	SoundManager::getIns()->load(toString(ResourceID::WideChangeSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::WideChangeSE)));
	SoundManager::getIns()->load(toString(ResourceID::KilledSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::KilledSE)));

	SoundManager::getIns()->load(toString(ResourceID::TitleBGM), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::TitleBGM)));
	SoundManager::getIns()->load(toString(ResourceID::Stage1), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::Stage1)));

	Parameter parameter;
	//�����ύX���邱�ƂŎn�܂�V�[����ς����
	//_sceneStack.push(std::make_shared<TitleScene>(this, parameter));
	_sceneStack.push(std::make_shared<GameScene>(this, parameter));
	
	_sceneStack.top()->Initialize();
	
	SoundManager::getIns()->set(saveData._bgmVolume);

}

Looper::~Looper()
{
	_sceneStack.top()->Finalize();
	ImageManager::getIns()->releaseAll();
	SoundManager::getIns()->releaseAll();
	SavedataUtils::SaveBinary(GlobalStatusManager::getIns()->GetGlobalStatus());
}

bool Looper::loop() 
{
	if (!_exitGame) {
		_sceneStack.top()->Update();
		_sceneStack.top()->Draw();
		
		_keyboard->update();

		_fps.draw();
		_fps.wait();
		return true;
	}
	else {
		return false;
	}

	
}

void Looper::onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) {
	_sceneStack.top()->Finalize();
	if (stackClear == true) {
		while (!_sceneStack.empty()) {
			//������pop����Ă��|�C���^����������邾���ŃX�^�b�N��Ɋ֐��͒��܂��Ă���̂Œ��ӁB������return�܂ŌĂ΂�邩�珜�������|�C���^�ւ̃A�N�Z�X�ɂȂ�₷���B
			_sceneStack.pop();
		}
	}


	switch(nextScene) {
		case Title:
			_sceneStack.push(std::make_shared<TitleScene>(this, parameter));
			break;
		case Game:
			_sceneStack.push(std::make_shared<GameScene>(this, parameter));
			break;
		case Musium:
			_sceneStack.push(std::make_shared<MusiumScene>(this, parameter));
			break;
		default:
			ERR("�����ȃV�[���ł�");
	}
	_sceneStack.top()->Initialize();
}

void Looper::exitGame() {
	_exitGame = true;
}