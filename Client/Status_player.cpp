#include "pch.h"
#include "Status_player.h"
#include "Player.h"
#include "Manager_player.h"

Status::Status(Player* player):player(player)
{
}

//--------------------idleleft----------------------

IdleLeft::IdleLeft(Player* player):Status(player)
{

}

void IdleLeft::on_enter()
{
	player->set_animation("idle_left");
}

void IdleLeft::on_exit()
{
}

void IdleLeft::on_update(double delta_time)
{
	Vector2D dir= player->get_move_dir();
	if (player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("run_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("run_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("run_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("run_front");
	}
}

//--------------------idleright----------------------
IdleRight::IdleRight(Player* player):Status(player)
{
}

void IdleRight::on_enter()
{
	player->set_animation("idle_right");
}

void IdleRight::on_exit()
{
}

void IdleRight::on_update(double delta_time)
{
	Vector2D dir = player->get_move_dir();
	if (player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("run_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("run_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("run_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("run_front");
	}
}

//--------------------idleup----------------------
IdleUp::IdleUp(Player* player) :Status(player)
{
}

void IdleUp::on_enter()
{
	player->set_animation("idle_back");

}

void IdleUp::on_exit()
{
}

void IdleUp::on_update(double delta_time)
{
	Vector2D dir = player->get_move_dir();
	if (player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("run_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("run_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("run_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("run_front");
	}
}
//--------------------idleup----------------------

IdleDown::IdleDown(Player* player):Status(player)
{
}

void IdleDown::on_enter()
{
	player->set_animation("idle_front");
}

void IdleDown::on_exit()
{
}

void IdleDown::on_update(double delta_time)
{
	Vector2D dir = player->get_move_dir();
	if (player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("run_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("run_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("run_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("run_front");
	}
}

//--------------------runleft----------------------

RunLeft::RunLeft(Player* player):Status(player)
{
}

void RunLeft::on_enter()
{
	player->set_animation("run_left");
}

void RunLeft::on_exit()
{
}

void RunLeft::on_update(double delta_time)
{
	Vector2D dir = player->get_move_dir();
	if (!player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("idle_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("idle_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("idle_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("idle_front");
	}
}
//--------------------runright----------------------

RunRight::RunRight(Player* player) :Status(player)
{
}

void RunRight::on_enter()
{
	player->set_animation("run_right");
}

void RunRight::on_exit()
{
}

void RunRight::on_update(double delta_time)
{
	Vector2D dir = player->get_move_dir();
	if (!player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("idle_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("idle_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("idle_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("idle_front");
	}
}
//--------------------runup----------------------

RunUp::RunUp(Player* player) :Status(player)
{
}

void RunUp::on_enter()
{
	player->set_animation("run_back");

}

void RunUp::on_exit()
{
}

void RunUp::on_update(double delta_time)
{
	Vector2D dir = player->get_move_dir();
	if (!player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("idle_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("idle_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("idle_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("idle_front");
	}
}
//--------------------rundown----------------------

RunDown::RunDown(Player* player) :Status(player)
{
}

void RunDown::on_enter()
{
	player->set_animation("run_front");

}

void RunDown::on_exit()
{
}

void RunDown::on_update(double delta_time)
{
	Vector2D dir = player->get_move_dir();
	if (!player->can_move()) {
		if (dir.x < 0)player->get_statusMachine()->switch_to("idle_left");
		if (dir.x > 0)player->get_statusMachine()->switch_to("idle_right");
		if (dir.y < 0)player->get_statusMachine()->switch_to("idle_back");
		if (dir.y > 0)player->get_statusMachine()->switch_to("idle_front");
	}
}
