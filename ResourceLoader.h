#pragma once
#include "Singleton.h"
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>


class ResourceLoader : public Singleton<ResourceLoader>
{
public:
	void loadFromJson(const std::string& filepath);

	const std::string& getImagePath(const std::string& tag) const;
	const std::string& getSoundPath(const std::string& tag) const;

private:
	std::unordered_map<std::string, std::string> _imageMap;
	std::unordered_map<std::string, std::string> _soundMap;
};

