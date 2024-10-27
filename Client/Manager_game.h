#pragma once
#include "Manager.h"
#include "Camera.h"
#include "Manager_player.h"

#include <SDL.h>

class Sentence;
class Manager_game :public Manager<Manager_game>
{
	friend class Manager<Manager_game>;
public:
	int run(int argc, char** argv);

	SDL_Renderer* get_renderer()const { return renderer; }
	SDL_Window* get_window()const { return window; }
	Camera* get_camera()const { return camera; }

protected:
	Manager_game();
	~Manager_game();

private:
	void on_input(const SDL_Event* event);

	void on_update(double delta_time);

	void on_draw();

	void init_assert(bool flag,const char* text);
	void init();
private:
	bool is_debug = false;

	int FPS = 60;

	int cur_coin_count = 0;
	int cur_home_hp = 10;

	bool is_quit = false;


	Camera *camera = nullptr;;

	SDL_Event event;

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;

	//manager
	Manager_player* manager_player = nullptr;
};


