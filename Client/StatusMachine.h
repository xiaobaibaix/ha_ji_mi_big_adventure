#pragma once
#include "Status_player.h"

#include <unordered_map>


class StatusMachine
{
public:

	void entry(const std::string& id);

	void on_update(double delta_time);

	void switch_to(const std::string& id);

	void register_status(const std::string& id, Status* status);
private:
	std::unordered_map<std::string, Status*> status_pool;
	Status* status_cur = nullptr;
};

