#pragma once
#include <map>
#include <string>

//�I�����Ƃ���map��n���Ε\�����Ă����N���X
class Choices
{
public:
	Choices(const std::map<int, std::string>& choices);
	//���i��0��Ԃ��A�G���^�[�L�[�������ꂽ���ɉ�����Ă��鍀�ڂ̔ԍ���Ԃ�
	int Update();
	void Draw() const;

private:
	std::map<int, std::string> _choices;
	int itemNum;
	int nowSelect;
};

