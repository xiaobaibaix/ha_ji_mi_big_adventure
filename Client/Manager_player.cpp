#include "pch.h"
#include "Manager_player.h"
#include "PlayerHajimi.h"
#include "PlayerManbo.h"

Manager_player::Manager_player()
{
    player_pool["hajimi"] = new PlayerHajimi();
    player_pool["manbo"] = new PlayerManbo();

    player_pool["hajimi"]->setPos({ 500,500 });
    player_pool["manbo"]->setPos({400,400});
}

Manager_player::~Manager_player()
{
    for (auto& pair : player_pool) {
        delete pair.second; // 删除指向 Player 对象的指针
    }
    player_pool.clear(); // 然后清空哈希表
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
    for (auto& player : player_pool) {
        player.second->on_update(delta_time);
    }
}

void Manager_player::on_draw()
{
    for (auto& player : player_pool) {
        player.second->on_draw();
    }
}
