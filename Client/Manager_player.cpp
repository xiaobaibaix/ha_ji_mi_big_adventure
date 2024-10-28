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

    cur_sentence->set_sentence(manager_sentence->get_sentence());
    cur_sentence->set_pos({ 0,380 });

    timer_input.set_one_shot(false);
    timer_input.set_wait_time(0.2);
    timer_input.set_on_timeout(
        [&]() {
            char c = cur_sentence->get_char();
            cur_sentence->add_idx();
            if (c == ' ' || c == '.') {
                if(self)self->setMoveTime(0.8);
                if (c == '.') {
                    Manager_sentence::instance()->add_idx();
                    cur_sentence->set_sentence(Manager_sentence::instance()->get_sentence());
                }
                if (client_id[0] == '1') {
                    progress_1++;
                }
                else {
                    progress_2++;
                }
            }
        }
    );
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
        player_pool["hajimi"] = self= new PlayerHajimi(Player::PlayerId::Self);
        player_pool["manbo"] = other=new PlayerManbo(Player::PlayerId::Other);
        client_id = '1';
        progress_1 = 0;
        Camera* camera = Manager_game::instance()->get_camera();
        camera->move_to({ player_pool["hajimi"]->getPosition().x - camera->get_size().x / 2+ player_pool["hajimi"]->get_size().x/2,
            player_pool["hajimi"]->getPosition().y - camera->get_size().y / 2 + player_pool["hajimi"]->get_size().y / 2 });
    }
    else if(id[0]=='2') {
        std::cout << "creat player manbo successful!" << std::endl;
        player_pool["hajimi"] =other= new PlayerHajimi(Player::PlayerId::Other);
        player_pool["manbo"] = self=new PlayerManbo(Player::PlayerId::Self);
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
    //timer_input.on_update(delta_time);
    if (!is_net_init) {
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

    if (!(progress_1 >= 0 && progress_2 >= 0)) {
        auto res_login = client->Post("/can_game");
        if (res_login && res_login->status == 200) {
            if (res_login->body.c_str()[0] == '1') {
                std::cerr << "game start!" << std::endl;

                if (client_id[0] == '1') {
                    progress_1 = 0;
                    progress_2 = 0;
                }
                else {
                    progress_1 = 0;
                    progress_2 = 0;
                }
            }
            else {
                std::cerr << "can not game!" << std::endl;
            }
        }
        else {
            std::cerr << "can_game Failed" << std::endl;
        }
    }

    for (auto& player : player_pool) {
        player.second->on_update(delta_time);
        if (!(progress_1 >= 0 && progress_2 >= 0))continue;
        if (player.second->getId() == Player::PlayerId::Self) {//本机
            char c = player.second->pressed_key_code();
            if (c != '\0'&&cur_sentence->get_char()==c) {
                word.push_back(c);
                cur_sentence->add_idx();
                if (c == ' '|| c == '.') {
                    word.clear();
                    player.second->setMoveTime(0.8);
                    if (c == '.') {
                        Manager_sentence::instance()->add_idx();
                        cur_sentence->set_sentence(Manager_sentence::instance()->get_sentence());
                    }
                    if (client_id[0] == '1') {
                        progress_1++;
                    }
                    else {
                        progress_2++;
                    }
                }
            }
        }
        else {//其他
            if (client_id[0] == '1') {
                std::string update_1_body = std::to_string(progress_1); // 示例数据
                auto res_update_1 = client->Post("/update_1", update_1_body, "text/plain");
                if (res_update_1 && res_update_1->status == 200) {
                    int progress = std::stoi(res_update_1->body);
                    if (progress - progress_2 > 0) {
                        if (other)other->setMoveTime(0.8);
                        progress_2 = progress;
                    }
                }
                else {
                    std::cerr << "Update 1 Failed" << std::endl;
                }
            }
            else {
                std::string update_2_body = std::to_string(progress_2); // 示例数据
                auto res_update_2 = client->Post("/update_2", update_2_body, "text/plain");
                if (res_update_2 && res_update_2->status == 200) {
                    int progress = std::stoi(res_update_2->body);
                    if (progress - progress_1 > 0) {
                        if (other)other->setMoveTime(0.8);
                        progress_1 = progress;
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

Player* Manager_player::get_other_player()
{
    return other;
}

