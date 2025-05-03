#include "Image.h"
#include <DxLib.h>

Image::Image()
{
	_player = myLoadGraph("images/Player.png");
}

void Image::load() {

}

void Image::release() {
	const int size = _images.size();
	for (int i = 0; i < size; i++) {
		DeleteGraph(_images[i]);
	}
	_images.clear();
}

int Image::getPlayer() const {
	return _player;
}

int Image::myLoadGraph(const char* fileName)
{
	int ret = LoadGraph(fileName);
	_images.push_back(ret);
	return ret;
}

int Image::myLoadDivGraph(const char* fileName, int n, int xn, int yn, int w, int h, int* buf)
{
	int ret = LoadDivGraph(fileName, n, xn, yn, w, h, buf);
	for (int i = 0; i < n; i++) {
		_images.push_back(buf[i]);
	}
	return ret;
}