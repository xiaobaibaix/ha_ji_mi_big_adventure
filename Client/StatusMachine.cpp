#include "pch.h"
#include "StatusMachine.h"

void StatusMachine::entry(const std::string& id)
{
	switch_to(id);

}

void StatusMachine::on_update(double delta_time)
{
	status_cur->on_update(delta_time);
}

void StatusMachine::switch_to(const std::string& id)
{
	if (status_pool.find(id)->second) {
		if (status_cur)status_cur->on_exit();
		status_pool[id]->on_enter();
		status_cur = status_pool[id];
	}
}

void StatusMachine::register_status(const std::string& id, Status* status)
{
	
	if (status_pool.find(id)== status_pool.end()) {
		status_pool[id] = status;
	}
	else {
		std::cout << "status already exist!" << std::endl;
	}
}
