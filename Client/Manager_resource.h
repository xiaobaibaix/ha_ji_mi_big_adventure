#pragma once
#include "Manager.h"
#include "Atlas.h"

#include <unordered_map>

class Manager_resource :
    public Manager<Manager_resource>
{
    friend class Manager<Manager_resource>;
public:
    void load();

    SDL_Texture* find_texture(std::string id);
    Atlas* find_atlas(std::string id);
private:

    struct AtalsPath
    {
        std::string path;
        int num;
    };
private:

    Manager_resource();
    ~Manager_resource();

    bool assert_load(bool ret, std::string text, std::string title);

private:
    std::unordered_map<std::string,SDL_Texture*> img_pool;
    std::unordered_map<std::string,Atlas*> atlas_pool;
};

