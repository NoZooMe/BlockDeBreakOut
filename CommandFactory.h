#pragma once]

#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "BulletCommand.h"

class CommandFactory
{
public:
	static std::shared_ptr<BulletCommand> CreateFromJSON(const nlohmann::json& j);
};

