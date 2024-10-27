#include "pch.h"
#include "PlayerManbo.h"
#include "Manager_resource.h"

PlayerManbo::PlayerManbo(PlayerId id):Player(id)
{
	auto* res = Manager_resource::instance();

	std::string ids[] = {
		"idle_back",
		"idle_front",
		"idle_left",
		"idle_right",
		"run_back",
		"run_front",
		"run_left",
		"run_right"
	};

	//¶¯»­
	for (int i = 0; i < ids->size()-1; i++) {
		Animation* animation = new Animation();
		animation->set_ancher_mode(Animation::AncherMode::Centerd);
		animation->set_interval(0.1);
		animation->set_loop(true);
		animation->add_frame(res->find_atlas("manbo_"+ids[i]));
		animation_pool[ids[i]] = animation;
	}

	//×´Ì¬
	status_machine.register_status(ids[0], new IdleUp(this));
	status_machine.register_status(ids[1], new IdleDown(this));
	status_machine.register_status(ids[2], new IdleLeft(this));
	status_machine.register_status(ids[3], new IdleRight(this));
	status_machine.register_status(ids[4], new RunUp(this));
	status_machine.register_status(ids[5], new RunDown(this));
	status_machine.register_status(ids[6], new RunLeft(this));
	status_machine.register_status(ids[7], new RunRight(this));
	status_machine.entry("idle_right");

	setPos(route.get_cur());

}

PlayerManbo::~PlayerManbo()
{
}

void PlayerManbo::on_input(const SDL_Event* event)
{
	Player::on_input(event);
}

void PlayerManbo::on_update(double delta_time)
{
	Player::on_update(delta_time);
}

void PlayerManbo::on_draw()
{
	Player::on_draw();
}
