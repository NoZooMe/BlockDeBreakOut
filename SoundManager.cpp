#include "SoundManager.h"
#include <DxLib.h>

void SoundManager::load(const std::string& tag, const std::string& filepath) {
	int handle = LoadSoundMem(filepath.c_str());
	_soundHandles[tag] = handle;
}

void SoundManager::release(const std::string& tag) {
	if (_soundHandles.count(tag)) {
		DeleteSoundMem(_soundHandles[tag]);
		_soundHandles.erase(tag);
		
	}
}

void SoundManager::releaseAll() {
	for (auto& [tag, handle] : _soundHandles) {
		DeleteSoundMem(handle);
	}

	_soundHandles.clear();
}

void SoundManager::play(const std::string& tag, bool loop) {
	auto it = _soundHandles.find(tag);
	if (it != _soundHandles.end()) {
		ChangeVolumeSoundMem(150, it->second);
		PlaySoundMem(it->second, loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK, TRUE);
	}
}

void SoundManager::stop(const std::string& tag) {
	auto it = _soundHandles.find(tag);
	if (it != _soundHandles.end()) {
		StopSoundMem(it->second);
	}
}