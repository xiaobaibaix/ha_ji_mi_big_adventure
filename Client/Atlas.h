#pragma once
#include <SDL.h>

#include <vector>
#include <string>

class Atlas {
public:

	Atlas() = default;
	~Atlas() = default;

	void load(std::string path, int num);

	void clear();

	int get_size()const;

	SDL_Texture* get_image(int idx);

	void add_image(SDL_Texture* img);
private:
	std::vector<SDL_Texture*> img_list;
};