#pragma once
#include "Fps.h"
#include "ISceneChangedListener.h"
#include "AbstractScene.h"
#include "Keyboard.h"
#include <memory>
#include <stack>

class Looper final : public ISceneChangedListener
{
public:
	Looper();
	~Looper();
	bool loop();
	void onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) override;

private:
	Fps _fps;
	std::stack<std::shared_ptr<AbstractScene>> _sceneStack;
	//Singleton�̓X�}�[�g�|�C���^����Ȃ��Ă����c�c�̂��ȁH
	Keyboard* _keyboard;
};

