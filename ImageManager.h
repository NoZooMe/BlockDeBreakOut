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
    //�^����ꂽtag�ɉ摜�����[�h
    int loadSingle(const std::string& tag, const std::string& filepath);
    void load(const std::string& tag, const std::string& filepath) override;
    void release(const std::string& tag) override;
    void releaseAll() override;

    int getImage(const std::string& tag) const;
    const std::vector<int>& getImageList(const std::string& tag) const;

private:
    //1�̃^�O��1�̃R���e�i���Ή�
    std::unordered_map<std::string, std::vector<int>> _images;
    //1�̃^�O��1�̒l���Ή�
    std::unordered_map<std::string, int> _singleImages;
};

