#include "pch.h"

#include "Atlas.h"
#include <SDL_image.h>
#include "Manager_game.h"


void Atlas::load(std::string path, int num) {
	img_list.clear();
	img_list.resize(num);

	SDL_Renderer* renderer = Manager_game::instance()->get_renderer();

	for (int i = 0; i < num;i++) {
		std::string  path_pic= path + "_"+std::to_string(i + 1)+".png";
		img_list[i]=IMG_LoadTexture(renderer, path_pic.c_str());
	}
}

void Atlas::clear() {
	img_list.clear();
}

int Atlas::get_size() const {
	return (int)img_list.size();
}

SDL_Texture* Atlas::get_image(int idx) {
	if (idx < 0 || idx >= img_list.size())return nullptr;
	return img_list[idx];
}

void Atlas::add_image(SDL_Texture* img) {
	img_list.push_back(img);
}
