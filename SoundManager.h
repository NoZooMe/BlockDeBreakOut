#pragma once
#include "IResourceManager.h"
#include "Singleton.h"
#include <unordered_map>
#include <string>
class SoundManager :
    public IResourceManager, public Singleton<SoundManager>
{
public:
    void load(const std::string& tag, const std::string& filepath) override;
    void release(const std::string& tag) override;
    void releaseAll() override;

    void play(const std::string& tag, bool loop = false);
    void stop(const std::string& tag);

private:
    std::unordered_map<std::string, int> _soundHandles;
};

