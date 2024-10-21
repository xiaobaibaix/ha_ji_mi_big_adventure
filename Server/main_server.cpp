#include <iostream>

#include "pch.h"


int main(int argc,char**argv) {

	std::cout << "this is server" << std::endl;
	httplib::Server server;
	
	server.Post("/hello", [&](const httplib::Request&req,httplib::Response& res) {
		std::cout << "hello from client!" << std::endl;

		res.set_content("hello from server", "text/plain");
		}
	);

	server.listen("localhost", 25565);

	system("pause");
	return 0;
}