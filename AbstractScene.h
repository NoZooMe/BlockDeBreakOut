#pragma once
#include "Task.h"
#include "ISceneChangedListener.h"
#include "Parameter.h"
class AbstractScene : public Task
{
protected:
	ISceneChangedListener* _implSceneChangedListener;
	Parameter _parameter;

public:
	AbstractScene(ISceneChangedListener* impl, const Parameter& parameter);
	virtual ~AbstractScene() = default;
};

