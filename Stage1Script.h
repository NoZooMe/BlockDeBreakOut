#pragma once

#include "StageScriptBase.h"
#include "BulletEvent.h"
#include "BulletCommand.h"
#include <string>
#include <vector>

class Stage1Script : public StageScriptBase {
public:
	//����1�̃R���X�g���N�^�ɕt���Ă����ƈÖق̌^�ϊ����֎~�ł���
	//Stage1Script s = "Stage1.json"�Ƃ������������֎~
	explicit Stage1Script(const std::string& scriptPath, const std::string& commandPath);
	void Update(int cnt, BulletMgr& bulletMgr, const Player& player, const Ball& ball) override;

private:
	std::vector<BulletEvent> _events;
	
	std::vector<BulletCommand::TimedCommand> _commands;
};

