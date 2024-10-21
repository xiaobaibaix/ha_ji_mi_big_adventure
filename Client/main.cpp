#define SDL_MAIN_HANDLED
#include <iostream>

#include "Manager_game.h"

int main(int argc, char** argv) {

	std::cout << "hello client" << std::endl;
	return Manager_game::instance()->run(argc,argv);
}