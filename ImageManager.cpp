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
		//_images[tag]にあてはまるようなhandleを全てforで回る
		for (int handle : _images[tag]) {
			DeleteGraph(handle);
		}
		_images.erase(tag);
	}
	_singleImages.erase(tag);
}

void ImageManager::releaseAll() {
	//_imagesの中の全ての[tag, handles]の組み合わせを周る
	for (auto& [tag, handles] : _images) {
		//今、handlesはvector<int>になっている。その中のintを周る
		for (int h : handles) {
			//handlesの中にloadされている値を消去(DxLib)
			DeleteGraph(h);
		}
	}
	//_imagesと_singleImagesを全て消去
	_images.clear();
	_singleImages.clear();
}

int ImageManager::getImage(const std::string& tag) const {
	auto it = _singleImages.find(tag);
	//存在すればvalue部(second)を取り出す
	return (it != _singleImages.end()) ? it->second : -1;
}

const std::vector<int>& ImageManager::getImageList(const std::string& tag) const {
	static const std::vector<int> empty;
	auto it = _images.find(tag);
	return (it != _images.end()) ? it->second : empty;
}