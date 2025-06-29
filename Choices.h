#pragma once
#include <map>
#include <string>

//選択肢としてmapを渡せば表示してくれるクラス
class Choices
{
public:
	Choices(const std::map<int, std::string>& choices);
	Choices(const std::map<int, std::string>& choices, int x, int y, bool isMove);
	//普段は0を返し、エンターキーが押された時に押されている項目の番号を返す
	int Update();
	void Draw() const;

private:
	std::map<int, std::string> _choices;
	int itemNum;
	int nowSelect;
	int _x;
	int _y;
	bool _isMove;
};

