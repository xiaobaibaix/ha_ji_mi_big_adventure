#include "Manager_game.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL2_gfxPrimitives.h>

#include <cmath>
#include <tchar.h>

int Manager_game::run(int argc, char** argv) {

	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_fre = SDL_GetPerformanceFrequency();
	while (!is_quit)
	{
		while (SDL_PollEvent(&event)) {
			on_input(&event);
		}
		const Uint64 cur_counter = SDL_GetPerformanceCounter();
		const double delta_time = (double)(cur_counter - last_counter) / counter_fre;
		last_counter = cur_counter;
		if (delta_time * 1000 < 1000.0f / FPS) {
			SDL_Delay((Uint32)(1000.0 / FPS - delta_time * 1000));
		}
		on_update(delta_time);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		on_draw();

		SDL_RenderPresent(renderer);

	}
	return 0;
}


Manager_game::Manager_game() 
{
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL 初始化失败");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"IMG 初始化失败");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"Mix 初始化失败");
	init_assert(!TTF_Init(), u8"TTF 初始化失败");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");


	window = SDL_CreateWindow("Secret_Adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	init_assert(window, u8"创建窗口失败");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(renderer, u8"创建渲染器失败");

}

Manager_game::~Manager_game() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Manager_game::init_assert(bool flag, const char* text) {
	if (flag)return;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败!", text, window);
}


void Manager_game::on_input(const SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT://程序退出
		is_quit = true;
		break;

	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_TAB) {
			// Tab键被按下
			is_debug = !is_debug;
		}
		break;
	default:
		break;
	}
}

void Manager_game::on_update(double delta_time) {

}

void Manager_game::on_draw() {

}
