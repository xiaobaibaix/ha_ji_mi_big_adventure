#include "pch.h"
#include "Manager_game.h"
#include "Manager_resource.h"

int Manager_game::run(int argc, char** argv) {

	init();

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
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL ��ʼ��ʧ��");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"IMG ��ʼ��ʧ��");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"Mix ��ʼ��ʧ��");
	init_assert(!TTF_Init(), u8"TTF ��ʼ��ʧ��");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");


	window = SDL_CreateWindow("Secret_Adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	init_assert(window, u8"��������ʧ��");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(renderer, u8"������Ⱦ��ʧ��");

	

}

Manager_game::~Manager_game() {

	delete camera;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();


}

void Manager_game::init_assert(bool flag, const char* text) {
	if (flag)return;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"��Ϸ����ʧ��!", text, window);
}

void Manager_game::init()
{
	Manager_resource::instance()->load();

	camera = new Camera({ 0,0 }, { 640,480 });
	//camera->mulX(2);
	camera->move_dalta({ 50,0 });

	manager_player = Manager_player::instance();

}


void Manager_game::on_input(const SDL_Event* event) {
	switch (event->type) {
	case SDL_QUIT://�����˳�
		is_quit = true;
		break;

	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_TAB) {
			// Tab��������
			is_debug = !is_debug;
		}
		break;
	default:
		break;
	}
	camera->on_input(event);
	manager_player->on_input(event);
}

void Manager_game::on_update(double delta_time) {

	camera->on_update(delta_time);
	manager_player->on_update(delta_time);
}

void Manager_game::on_draw() {

	static auto* bk = Manager_resource::instance()->find_texture("bk");
	SDL_Rect src_rect = { (int)camera->get_pos().x,(int)camera->get_pos().y,(int)camera->get_size().x,(int)camera->get_size().y };
	SDL_Rect dst_rect = {0,0,640,480};

	SDL_RenderCopy(renderer,bk, &src_rect, &dst_rect);
	
	manager_player->on_draw();
}
