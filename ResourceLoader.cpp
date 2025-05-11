#include "ResourceLoader.h"
#include <fstream>

void ResourceLoader::loadFromJson(const std::string& filepath) {
	std::ifstream file(filepath);
	nlohmann::json j;
	file >> j;

	for (auto& [tag, path] : j["Image"].items()) {
		_imageMap[tag] = path;
	}
	for (auto& [tag, path] : j["Sound"].items()) {
		_soundMap[tag] = path;
	}
}

const std::string& ResourceLoader::getImagePath(const std::string& tag) const {
	return _imageMap.at(tag);
}

const std::string& ResourceLoader::getSoundPath(const std::string& tag) const {
	return _soundMap.at(tag);
}