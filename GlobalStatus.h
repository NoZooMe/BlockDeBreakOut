#pragma once

struct GlobalStatus {
	int _highScore = 0;
	bool _isEnterTitle = false;
	bool _isEnterStage1 = false;
	bool _isClearStage1 = false;
	bool _isNoContinueStage1 = false;

	int _bgmVolume = 255;
	int _seVolume = 255;
};