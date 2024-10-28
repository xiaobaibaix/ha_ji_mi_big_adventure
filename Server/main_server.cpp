#include "pch.h"

#include <mutex>
#include <string>
#include <fstream>
#include <iostream>

std::mutex g_mutex;

std::string str_text;

int progress_1 = -1;
int progress_2 = -1;

int main(int argc,char**argv) {
	//文件读取
	std::ifstream file("./res/text.txt");

	if (!file.good()) {
		MessageBox(nullptr, L"无法打开文件 text.txt", L"启动失败", MB_OK | MB_ICONERROR);
		return -1;
	}
	std::stringstream str_stream;
	str_stream << file.rdbuf();

	str_text = str_stream.str();

	file.close();

	httplib::Server server;
	
	server.Post("/login", [&](const httplib::Request&req,httplib::Response& res) {
		std::lock_guard<std::mutex> lock(g_mutex);

		if (progress_1>=0&&progress_2>=0) {
			res.set_content("-1", "text/plain");
			return;
		}
		res.set_content(progress_1 >= 0 ? "2" : "1", "text/plain");
		progress_1 >= 0 ? (progress_2 = 0):(progress_1 = 0);
		if (progress_1 >= 0 && progress_2 >= 0) {
			std::cout << "game start!" << std::endl;
		}
		}
	);

	server.Post("/query_text", [&](const httplib::Request& req, httplib::Response& res) {
		std::lock_guard<std::mutex> lock(g_mutex);
		res.set_content(str_text, "text/plain");
		}
	);

	server.Post("/update_1", [&](const httplib::Request& req, httplib::Response& res) {
		std::lock_guard<std::mutex> lock(g_mutex);

		progress_1 = std::stoi(req.body);
		std::cout << "profress_1:" << progress_1 << std::endl;
		res.set_content(std::to_string(progress_2), "text/plain");
		}
	);

	server.Post("/update_2", [&](const httplib::Request& req, httplib::Response& res) {
		std::lock_guard<std::mutex> lock(g_mutex);

		progress_2 = std::stoi(req.body);
		
		res.set_content(std::to_string(progress_1), "text/plain");
		}
	);

	server.listen("localhost", 25565);
	return 0;
}