#pragma once
#include "eScene.h"
class Parameter;

class  ISceneChangedListener{
public:
	ISceneChangedListener() = default;
	virtual ~ISceneChangedListener() = default;

	virtual void onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) = 0;
	virtual void exitGame() = 0;
};