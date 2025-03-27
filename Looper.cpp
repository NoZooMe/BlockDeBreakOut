#include "Looper.h"
#include "TitleScene.h"
#include "GameScene.h"

Looper::Looper()
{
	_keyboard = _keyboard->getIns();
	Parameter parameter;
	_sceneStack.push(std::make_shared<TitleScene>(this, parameter));
}

Looper::~Looper()
{
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
}