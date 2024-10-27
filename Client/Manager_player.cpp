#include "pch.h"
#include "Manager_player.h"
#include "PlayerHajimi.h"
#include "PlayerManbo.h"
#include "Manager_game.h"

Manager_player::Manager_player()
{
    manager_sentence=Manager_sentence::instance();

    // 发送POST请求到/query_text路由
    auto res_query = client->Post("/query_text");
    if (res_query && res_query->status == 200) {
        manager_sentence->set_text(res_query->body);
        std::cout << "set text successful!" << std::endl;
    }
    else {
        std::cerr << "Query Text Failed" << std::endl;
    }

    cur_sentence = new Sentence();

    cur_sentence->set_sentence(manager_sentence->get_sentence(0));
    cur_sentence->set_pos({ 0,380 });
}

Manager_player::~Manager_player()
{
    for (auto& pair : player_pool) {
        delete pair.second; // 删除指向 Player 对象的指针
    }
    player_pool.clear(); // 然后清空哈希表
    delete cur_sentence;
}

void Manager_player::setPlayer(const std::string& id)
{
    if (id[0] == '1') {
        std::cout << "creat player hajimi successful!" << std::endl;
        player_pool["hajimi"] = new PlayerHajimi(Player::PlayerId::Self);
        player_pool["manbo"] = new PlayerManbo(Player::PlayerId::Other);
        client_id = '1';
        progress_1 = 0;
        Camera* camera = Manager_game::instance()->get_camera();
        camera->move_to({ player_pool["hajimi"]->getPosition().x - camera->get_size().x / 2+ player_pool["hajimi"]->get_size().x/2,
            player_pool["hajimi"]->getPosition().y - camera->get_size().y / 2 + player_pool["hajimi"]->get_size().y / 2 });
    }
    else if(id[0]=='2') {
        std::cout << "creat player manbo successful!" << std::endl;
        player_pool["hajimi"] = new PlayerHajimi(Player::PlayerId::Other);
        player_pool["manbo"] = new PlayerManbo(Player::PlayerId::Self);
        client_id = '2';
        progress_2 = 0;
        Camera* camera = Manager_game::instance()->get_camera();
        camera->move_to({ player_pool["manbo"]->getPosition().x - camera->get_size().x / 2 + player_pool["manbo"]->get_size().x / 2,
            player_pool["manbo"]->getPosition().y - camera->get_size().y / 2 + player_pool["manbo"]->get_size().y / 2 });
    }
}

Player* Manager_player::find_player(std::string id)
{
    if (player_pool.find(id) != player_pool.end()) {
        return player_pool[id];
    }
    else {
        return nullptr;
    }
}

void Manager_player::on_input(const SDL_Event* event)
{
    for (auto& player:player_pool) {
        player.second->on_input(event);
    }
}

void Manager_player::on_update(double delta_time)
{
    if (!is_net_init) {
        // 发送POST请求到/login路由
        auto res_login = client->Post("/login");
        if (res_login && res_login->status == 200) {
            std::cout << "login successful: " << res_login->body << std::endl;
            setPlayer(res_login->body);
        }
        else {
            std::cerr << "Login Failed" << std::endl;
        }
        is_net_init = true;
    }
    if (!can_game) {
        // 发送POST请求到/login路由
        auto res_login = client->Post("/can_game");
        if (res_login && res_login->status == 200) {
            std::cout << "game successful: " << res_login->body << std::endl;
            if (res_login->body.c_str()[0] == '1')can_game = true;
            else can_game = false;
        }
        else {
            std::cerr << "Login Failed" << std::endl;
        }
    }
    for (auto& player : player_pool) {
        player.second->on_update(delta_time);
        if (player.second->getId() == Player::PlayerId::Self) {
            char c = player.second->pressed_key_code();
            std::cout <<"sentence next char: " << cur_sentence->get_char() << std::endl;
            if (c != '\0'&&cur_sentence->get_char()==c) {
                player.second->addMoveTime(0.8);
                cur_sentence->add_idx();
                if (client_id[0] == '1') {
                    progress_1++;
                }
                else if(client_id[0]=='2') {
                    progress_2++;
                }
                std::cout << "输入成功！:" <<c<< std::endl;
            }
        }
        else {

            if (client_id[0] == '1') {
                // 发送POST请求到/update_1路由
                std::string update_1_body = std::to_string(progress_1); // 示例数据
                auto res_update_1 = client->Post("/update_1", update_1_body, "text/plain");
                if (res_update_1 && res_update_1->status == 200) {
                    //std::cout << "Update 1 Response: " << res_update_1->body << std::endl;
                    if (std::stoi(res_update_1->body)-progress_2>0) {
                        player.second->addMoveTime(0.8);
                        progress_2 = std::stoi(res_update_1->body);
                    }
                }
                else {
                    std::cerr << "Update 1 Failed" << std::endl;
                }
            }
            else {
                // 发送POST请求到/update_2路由
                std::string update_2_body = std::to_string(progress_2); // 示例数据
                auto res_update_2 = client->Post("/update_2", update_2_body, "text/plain");
                if (res_update_2 && res_update_2->status == 200) {
                    //std::cout << "Update 2 Response: " << res_update_2->body << std::endl;
                    if (std::stoi(res_update_2->body) - progress_1 > 0) {
                        player.second->addMoveTime(0.8);
                        progress_1 = std::stoi(res_update_2->body);
                    }
                }
                else {
                    std::cerr << "Update 2 Failed" << std::endl;
                }
            }
        }
    }
}

void Manager_player::on_draw()
{
    for (auto& player : player_pool) {
        player.second->on_draw();
    }

    cur_sentence->render_str_tex();
}
