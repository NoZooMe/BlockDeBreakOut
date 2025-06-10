#include "GlobalStatusManager.h"
#include "Macro.h"

GlobalStatusManager::GlobalStatusManager() {
	_globalStatus = { 0, false, false, false, false };
}

int GlobalStatusManager::GetHighScore() const {
	return _globalStatus._highScore;
}

bool GlobalStatusManager::GetGlobalFlag(eGlobalStatusFlag flag) const {
	switch (flag) {
	case eGlobalStatusFlag::TitleEnter:
		return _globalStatus._isEnterTitle;
		break;
	case eGlobalStatusFlag::Stage1Enter:
		return _globalStatus._isEnterStage1;
		break;
	case eGlobalStatusFlag::Stage1Clear:
		return _globalStatus._isClearStage1;
		break;
	case eGlobalStatusFlag::Stage1NoContinue:
		return _globalStatus._isNoContinueStage1;
		break;
	default:
		ERR("存在しないフラグです。");
		return false;
	}
}

GlobalStatus GlobalStatusManager::GetGlobalStatus() const {
	return _globalStatus;
}

void GlobalStatusManager::SetHighScore(const int highScore) {
	_globalStatus._highScore = highScore;
}

void GlobalStatusManager::SetGlobalFlag(eGlobalStatusFlag flag, bool value) {
	switch (flag) {
	case eGlobalStatusFlag::TitleEnter:
		_globalStatus._isEnterTitle = value;
		break;
	case eGlobalStatusFlag::Stage1Enter:
		_globalStatus._isEnterStage1 = value;
		break;
	case eGlobalStatusFlag::Stage1Clear:
		_globalStatus._isClearStage1 = value;
		break;
	case eGlobalStatusFlag::Stage1NoContinue:
		_globalStatus._isNoContinueStage1 = value;
		break;
	default:
		ERR("存在しないフラグに書き込もうとしています。");
	}
}

void GlobalStatusManager::SetGlobalStatus(const GlobalStatus& saveData) {
	_globalStatus = saveData;
}