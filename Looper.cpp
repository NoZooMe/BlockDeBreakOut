#include "Looper.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "ResourceLoader.h"
#include "ResourceID.h"
#include <DxLib.h>

Looper::Looper()
{
	_keyboard = _keyboard->getIns();

	//json内のresourceパスを全てロード
	ResourceLoader::getIns()->loadFromJson("resources.json");

	ImageManager::getIns()->load(toString(ResourceID::Player), ResourceLoader::getIns()->getImagePath(toString(ResourceID::Player)));

	SoundManager::getIns()->load(toString(ResourceID::BreakBlockSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::BreakBlockSE)));
	SoundManager::getIns()->load(toString(ResourceID::OpenMenuSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::OpenMenuSE)));
	SoundManager::getIns()->load(toString(ResourceID::SelectMenuSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::SelectMenuSE)));
	SoundManager::getIns()->load(toString(ResourceID::ShotBulletSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::ShotBulletSE)));
	SoundManager::getIns()->load(toString(ResourceID::DamageSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::DamageSE)));
	SoundManager::getIns()->load(toString(ResourceID::ReflectSE), ResourceLoader::getIns()->getSoundPath(toString(ResourceID::ReflectSE)));


	Parameter parameter;
	//ここ変更することで始まるシーンを変えれる
	//_sceneStack.push(std::make_shared<TitleScene>(this, parameter));
	_sceneStack.push(std::make_shared<GameScene>(this, parameter));
	
	_sceneStack.top()->Initialize();
	
	

}

Looper::~Looper()
{
	_sceneStack.top()->Finalize();
	ImageManager::getIns()->releaseAll();
	SoundManager::getIns()->releaseAll();
}

bool Looper::loop() 
{

	_sceneStack.top()->Update();
	_sceneStack.top()->Draw();

	_keyboard->update();

	_fps.draw();
	_fps.wait();
	return true;
}

void Looper::onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) {
	_sceneStack.top()->Finalize();
	if (stackClear == true) {
		while (!_sceneStack.empty()) {
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
		default:
			;
	}
	_sceneStack.top()->Initialize();
}