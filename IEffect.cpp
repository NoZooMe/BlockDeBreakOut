#include "IEffect.h"

IEffect::IEffect(int duration, int width, int height) : _duration(duration), _cnt(0), _deleteFlag(false), _w(width), _h(height){

}

void IEffect::Update() {
	_cnt++;
	if (_cnt >= _duration) {
		_deleteFlag = true;
	}
}

bool IEffect::GetterDeleteFlag() {
	return _deleteFlag;
}