#pragma once
#include <string>

class IResourceManager{
public:
	virtual ~IResourceManager() = default;
	virtual void load(const std::string& tag, const std::string& path) = 0;
	virtual void release(const std::string& tag) = 0;
	virtual void releaseAll() = 0;
};