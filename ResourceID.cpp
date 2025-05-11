#include "ResourceID.h"
#include <unordered_map>

const std::string& toString(ResourceID id) {
	static const std::unordered_map<ResourceID, std::string> table = {
		{ResourceID::Player, "Player"}, 

		{ResourceID::BreakBlockSE, "BreakBlockSE"}, 
		{ResourceID::DamageSE, "DamageSE"}, 
		{ResourceID::OpenMenuSE, "OpenMenuSE"}, 
		{ResourceID::SelectMenuSE, "SelectMenuSE"}, 
		{ResourceID::ShotBulletSE, "ShotBulletSE"}, 
		{ResourceID::ReflectSE, "ReflectSE"},

		{ResourceID::Stage1, "Stage1"}
	};
	return table.at(id);	//id‚ª–¢“o˜^‚È‚ç—áŠO‚É‚È‚é
}