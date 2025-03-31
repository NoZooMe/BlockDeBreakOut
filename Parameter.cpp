#include"Parameter.h"

void Parameter::set(std::string key, int val) {
	_map[key] = val;
}

int Parameter::get(std::string key) const {
	auto it = _map.find(key);

	if (_map.end() == it) {//無かったら
		return Error;
	}
	else {
		return it->second;	//あったら値を返す._mapの要素は_pair型として保存され、それぞれfirstとsecodで要素を取得できる
	}
}

int Parameter::getNum() const {
	int num = _map.size();
	return num;
}