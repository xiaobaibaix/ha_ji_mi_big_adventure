#include "pch.h"
#include "Net.h"

Net::Net()
{
	client = new httplib::Client("localhost", 25565);

    // 发送POST请求到/login路由
    auto res_login = client->Post("/login", "", "application/json");
    if (res_login && res_login->status == 200) {
        std::cout << "Login Response: " << res_login->body << std::endl;
    }
    else {
        std::cerr << "Login Failed" << std::endl;
    }

    // 发送POST请求到/query_text路由
    auto res_query = client->Post("/query_text", "", "application/json");
    if (res_query && res_query->status == 200) {
        std::cout << "Query Text Response: " << res_query->body << std::endl;
    }
    else {
        std::cerr << "Query Text Failed" << std::endl;
    }

    // 发送POST请求到/update_1路由
    std::string update_1_body = "{\"progress\": 10}"; // 示例数据
    auto res_update_1 = client->Post("/update_1", update_1_body, "application/json");
    if (res_update_1 && res_update_1->status == 200) {
        std::cout << "Update 1 Response: " << res_update_1->body << std::endl;
    }
    else {
        std::cerr << "Update 1 Failed" << std::endl;
    }

    // 发送POST请求到/update_2路由
    std::string update_2_body = "{\"progress\": 20}"; // 示例数据
    auto res_update_2 = client->Post("/update_2", update_2_body, "application/json");
    if (res_update_2 && res_update_2->status == 200) {
        std::cout << "Update 2 Response: " << res_update_2->body << std::endl;
    }
    else {
        std::cerr << "Update 2 Failed" << std::endl;
    }
}

Net::~Net()
{
	delete client;
}
