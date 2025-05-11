#pragma once
#include <string>
enum class ResourceID
{
	Player, 

	BreakBlockSE, 
	DamageSE, 
	OpenMenuSE, 
	SelectMenuSE, 
	ShotBulletSE, 
	ReflectSE,

	Stage1, 

	COUNT
};

//ïœä∑ä÷êî
const std::string& toString(ResourceID id);