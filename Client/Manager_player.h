#pragma once
#include "Manager.h"
#include "Player.h"
#include "Net.h"
#include "Sentence.h"
#include "Manager_sentence.h"

#include <unordered_map>

class Manager_player:public Manager<Manager_player>,public Net{
	friend class Manager<Manager_player>;
public:
	
	virtual void setPlayer(const std::string& id)override;

	Player* find_player(std::string id);

	void on_input(const SDL_Event* event);

	void on_update(double delta_time);

	void on_draw();

	Player* get_other_player();
private:
	Manager_player();
	~Manager_player();

private:
	Timer timer_input;
	std::string client_id;
	std::string word;

	int progress_1 = -1;
	int progress_2 = -1;

		
	bool can_game = false;

	Manager_sentence *manager_sentence = nullptr;
	Sentence* cur_sentence = nullptr;

	std::unordered_map<std::string, Player*> player_pool;
	Player* other = nullptr;
	Player* self = nullptr;
};

