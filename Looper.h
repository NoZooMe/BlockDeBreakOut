#pragma once
#include "Fps.h"
#include "ISceneChangedListener.h"
#include "AbstractScene.h"
#include <memory>
#include <stack>

class Keyboard;

class Looper final : public ISceneChangedListener
{
public:
	Looper();
	~Looper();
	bool loop();
	void onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) override;
	void exitGame() override;

private:
	Fps _fps;
	std::stack<std::shared_ptr<AbstractScene>> _sceneStack;
	//Singletonはスマートポインタじゃなくていい……のかな？ 勝手にデストラクタしてくれる？
	Keyboard* _keyboard;
	bool _exitGame;
};

