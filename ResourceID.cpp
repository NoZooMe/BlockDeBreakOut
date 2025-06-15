#include "ResourceID.h"
#include <unordered_map>

const std::string& toString(ResourceID id) {
	static const std::unordered_map<ResourceID, std::string> table = {
		{ResourceID::Player, "Player"}, 
		{ResourceID::Title, "Title"},
		{ResourceID::First, "First"},
		{ResourceID::Zero, "Zero"},

		{ResourceID::BreakBlockSE, "BreakBlockSE"}, 
		{ResourceID::DamageSE, "DamageSE"}, 
		{ResourceID::OpenMenuSE, "OpenMenuSE"}, 
		{ResourceID::SelectMenuSE, "SelectMenuSE"}, 
		{ResourceID::ShotBulletSE, "ShotBulletSE"}, 
		{ResourceID::ReflectSE, "ReflectSE"},
		{ResourceID::BombSE, "BombSE"},
		{ResourceID::EnemyAtackSE, "EnemyAtackSE"},
		{ResourceID::PowerUpSE, "PowerUpSE"},
		{ResourceID::LifeUpSE, "LifeUpSE"}, 
		{ResourceID::ScoreUpSE, "ScoreUpSE"},
		{ResourceID::WideChangeSE, "WideChangeSE"},
		{ResourceID::KilledSE, "KilledSE"},

		{ResourceID::TitleBGM, "TitleBGM"},
		{ResourceID::Stage1, "Stage1"}
	};
	return table.at(id);	//id‚ª–¢“o˜^‚È‚ç—áŠO‚É‚È‚é
}