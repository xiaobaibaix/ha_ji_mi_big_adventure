#pragma once
#include "Manager.h"

#include <SDL.h>

class Manager_game :public Manager<Manager_game>
{
	friend class Manager<Manager_game>;
public:
	int run(int argc, char** argv);

public:
	bool is_debug = false;
protected:
	Manager_game();
	~Manager_game();

private:
	void on_input(const SDL_Event* event);

	void on_update(double delta_time);

	void on_draw();

	void init_assert(bool flag,const char* text);

private:
	int FPS = 60;

	int cur_coin_count = 0;
	int cur_home_hp = 10;

	bool is_quit = false;


	SDL_Event event;

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;

	SDL_Texture* tex_tile_map = nullptr;

	//manager
};

