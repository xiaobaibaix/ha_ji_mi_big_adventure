#include "pch.h"
#include "Manager_game.h"
#define SDL_MAIN_HANDLED


int main(int argc, char** argv) {

	return Manager_game::instance()->run(argc,argv);

}