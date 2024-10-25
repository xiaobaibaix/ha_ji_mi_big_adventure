#pragma once
#include "Manager.h"
#include "Player.h"

#include <unordered_map>

class Manager_player:public Manager<Manager_player>
{
	friend class Manager<Manager_player>;
public:
	Player* find_player(std::string id);

	void on_input(const SDL_Event* event);

	void on_update(double delta_time);

	void on_draw();
private:
	Manager_player();
	~Manager_player();

private:
	std::unordered_map<std::string, Player*> player_pool;
};

