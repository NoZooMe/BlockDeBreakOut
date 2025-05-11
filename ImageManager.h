#pragma once
#include "IResourceManager.h"
#include "Singleton.h"
#include <unordered_map>
#include <vector>
#include <string>
class ImageManager final:
    public IResourceManager, public Singleton<ImageManager>
{
public:
    //与えられたtagに画像をロード
    int loadSingle(const std::string& tag, const std::string& filepath);
    void load(const std::string& tag, const std::string& filepath) override;
    void release(const std::string& tag) override;
    void releaseAll() override;

    int getImage(const std::string& tag) const;
    const std::vector<int>& getImageList(const std::string& tag) const;

private:
    //1つのタグに1つのコンテナが対応
    std::unordered_map<std::string, std::vector<int>> _images;
    //1つのタグに1つの値が対応
    std::unordered_map<std::string, int> _singleImages;
};

