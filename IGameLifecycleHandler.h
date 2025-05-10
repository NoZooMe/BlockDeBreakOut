#pragma once
class IGameLifeCycleHandler {
public:
	~IGameLifeCycleHandler() = default;

	virtual void RequestRestart() = 0;
	virtual void RequestContinue() = 0;
	virtual void RequestDamage() = 0;
	virtual void RequestClear() = 0;
};