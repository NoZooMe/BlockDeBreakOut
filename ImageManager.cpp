#include "ImageManager.h"
#include <DxLib.h>


int ImageManager::loadSingle(const std::string& tag, const std::string& filepath) {
	int handle = LoadGraph(filepath.c_str());
	_images[tag] = { handle };
	_singleImages[tag] = handle;
	return handle;
}

void ImageManager::load(const std::string& tag, const std::string& filepath) {
	loadSingle(tag, filepath);
}

void ImageManager::release(const std::string& tag) {
	if (_images.count(tag)) {
		//_images[tag]�ɂ��Ă͂܂�悤��handle��S��for�ŉ��
		for (int handle : _images[tag]) {
			DeleteGraph(handle);
		}
		_images.erase(tag);
	}
	_singleImages.erase(tag);
}

void ImageManager::releaseAll() {
	//_images�̒��̑S�Ă�[tag, handles]�̑g�ݍ��킹������
	for (auto& [tag, handles] : _images) {
		//���Ahandles��vector<int>�ɂȂ��Ă���B���̒���int������
		for (int h : handles) {
			//handles�̒���load����Ă���l������(DxLib)
			DeleteGraph(h);
		}
	}
	//_images��_singleImages��S�ď���
	_images.clear();
	_singleImages.clear();
}

int ImageManager::getImage(const std::string& tag) const {
	auto it = _singleImages.find(tag);
	//���݂����value��(second)�����o��
	return (it != _singleImages.end()) ? it->second : -1;
}

const std::vector<int>& ImageManager::getImageList(const std::string& tag) const {
	static const std::vector<int> empty;
	auto it = _images.find(tag);
	return (it != _images.end()) ? it->second : empty;
}