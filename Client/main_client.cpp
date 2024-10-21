#define SDL_MAIN_HANDLED
#include <iostream>

#include "Manager_game.h"
#include "pch.h"

int main(int argc, char** argv) {

	//std::cout << "hello client" << std::endl;
	//return Manager_game::instance()->run(argc,argv);

	std::cout << "this is client" << std::endl;

	httplib::Client client("localhost:25565");

	httplib::Result result = client.Post("/hello");

	if (!result || result->status != 200) {
		std::cout << "hello falied  " << std::endl;
		return -1;
	}

	std::cout << result->body << std::endl;

	system("pause");


}