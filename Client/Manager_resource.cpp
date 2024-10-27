#include "pch.h"
#include "Manager_resource.h"
#include "Manager_game.h"
#include "Atlas.h"

void Manager_resource::load()
{
	std::unordered_map<std::string, std::string> id_img_path = {
		{"bk","res/background.png"},
		{"ui_1","res/ui_1.png"},
		{"ui_2","res/ui_2.png"},
		{"ui_3","res/ui_3.png"},
		{"ui_fight","res/ui_fight.png"},
		{"ui_textbox","res/ui_textbox.png"}
	};

	std::unordered_map<std::string, std::string> id_font_path = {
	{"font","res/IPix.ttf"}
	};

	std::unordered_map<std::string,struct AtalsPath> id_atlas_path{
		{"hajimi_idle_back",{"res/hajimi_idle_back",4}},
		{"hajimi_idle_front",{"res/hajimi_idle_front",4}},
		{"hajimi_idle_left",{"res/hajimi_idle_left",4}},
		{"hajimi_idle_right",{"res/hajimi_idle_right",4}},
		{"hajimi_run_back",{"res/hajimi_run_back",4}},
		{"hajimi_run_front",{"res/hajimi_run_front",4}},
		{"hajimi_run_left",{"res/hajimi_run_left",4}},
		{"hajimi_run_right",{"res/hajimi_run_right",4}},
		{"manbo_idle_back",{"res/manbo_idle_back",4}},
		{"manbo_idle_front",{"res/manbo_idle_front",4}},
		{"manbo_idle_left",{"res/manbo_idle_left",4}},
		{"manbo_idle_right",{"res/manbo_idle_right",4}},
		{"manbo_run_back",{"res/manbo_run_back",4}},
		{"manbo_run_front",{"res/manbo_run_front",4}},
		{"manbo_run_left",{"res/manbo_run_left",4}},
		{"manbo_run_right",{"res/manbo_run_right",4}},
	};

	auto* renderer=Manager_game::instance()->get_renderer();

	//图片的加载
	for (auto& path:id_img_path) {
		img_pool[path.first]=IMG_LoadTexture(renderer, path.second.c_str());
		if (!assert_load(img_pool[path.first], path.second, "res load fail!！")) {
			exit(-1);
			return;
		}
	}

	for (auto& path : id_img_path) {
		img_pool[path.first] = IMG_LoadTexture(renderer, path.second.c_str());
		if (!assert_load(img_pool[path.first], path.second, "res load fail!！")) {
			exit(-1);
			return;
		}
	}

	//图集的加载
	for (auto& path : id_atlas_path) {
		atlas_pool[path.first] = new Atlas;
		atlas_pool[path.first]->load(path.second.path, path.second.num);
		for (int i = 0; i < path.second.num;i++) {
			if (!assert_load(atlas_pool[path.first]->get_image(i), path.second.path, "res load fail!！")) {
				exit(-1);
				return;
			}
		}

	}

}

SDL_Texture* Manager_resource::find_texture(std::string id)
{
	const auto& itor = img_pool.find(id);
	if (itor == img_pool.end())return nullptr;
	return itor->second;
}

Atlas* Manager_resource::find_atlas(std::string id)
{
	const auto& itor = atlas_pool.find(id);
	if (itor == atlas_pool.end())return nullptr;
	return itor->second;
}

std::string Manager_resource::find_font_path(std::string id)
{
	const auto& itor = id_font_path.find(id);
	if (itor == id_font_path.end())return nullptr;
	return itor->second;
}

Manager_resource::Manager_resource()
{
}

Manager_resource::~Manager_resource()
{
}

bool Manager_resource::assert_load(bool ret, std::string text, std::string title)
{
	if (ret)return true;
	auto* window = Manager_game::instance()->get_window();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), text.c_str(), window);
	return false;
}
