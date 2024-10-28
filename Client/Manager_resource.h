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
    std::string find_font_path(std::string id);
    const Mix_Chunk* get_sound_pool(std::string id) const;

    const Mix_Music* get_music_pool(std::string id) const;

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
    std::unordered_map<std::string, Atlas*> atlas_pool;
    std::unordered_map<std::string, Mix_Chunk*> sound_pool;
    std::unordered_map<std::string, Mix_Music*> music_pool;

    std::unordered_map<std::string, std::string> id_font_path = {
        {"font","res/IPix.ttf"}
    };
};

