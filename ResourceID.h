#pragma once
#include <string>
enum class ResourceID
{

	Player, 
	Title,
	First, 
	Zero,

	BreakBlockSE, 
	DamageSE, 
	OpenMenuSE, 
	SelectMenuSE, 
	ShotBulletSE, 
	ReflectSE,
	BombSE,
	EnemyAtackSE,
	LifeUpSE,
	PowerUpSE,
	ScoreUpSE,
	WideChangeSE,
	KilledSE,


	TitleBGM,
	Stage1, 

	COUNT
};

//ïœä∑ä÷êî
const std::string& toString(ResourceID id);