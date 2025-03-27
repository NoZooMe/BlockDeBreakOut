#pragma once
#include "Parameter.h"
#include "eScene.h"

class  ISceneChangedListener{
public:
	ISceneChangedListener() = default;
	virtual ~ISceneChangedListener() = default;

	virtual void onSceneChanged(const eScene nextScene, const Parameter& parameter, const bool stackClear) = 0;
};