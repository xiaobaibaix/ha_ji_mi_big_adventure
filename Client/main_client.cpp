#define SDL_MAIN_HANDLED
#include "pch.h"
#include "Manager_game.h"


int main(int argc, char** argv) {

	return Manager_game::instance()->run(argc,argv);

}