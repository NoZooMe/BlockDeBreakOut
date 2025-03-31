#include"Parameter.h"

void Parameter::set(std::string key, int val) {
	_map[key] = val;
}

int Parameter::get(std::string key) const {
	auto it = _map.find(key);

	if (_map.end() == it) {//����������
		return Error;
	}
	else {
		return it->second;	//��������l��Ԃ�._map�̗v�f��_pair�^�Ƃ��ĕۑ�����A���ꂼ��first��secod�ŗv�f���擾�ł���
	}
}

int Parameter::getNum() const {
	int num = _map.size();
	return num;
}