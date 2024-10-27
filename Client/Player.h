#pragma once

#include "Route.h"
#include "Animation.h"
#include "StatusMachine.h"

#include <unordered_map>


class Player
{
public:
	enum class PlayerId {
		None,
		Manbo,
		Hajimi
	};
public:
	Player(Player::PlayerId id);
	virtual ~Player();

	virtual void on_input(const SDL_Event* event);

	virtual void on_update(double delta_time);

	virtual void on_draw();

	Player::PlayerId getId();
	Vector2D getSpeed();
	Vector2D getPosition();
	char get_press_key_code();
	bool can_move();
	Vector2D get_move_dir();
	StatusMachine* get_statusMachine();

	void setSpeed(const Vector2D& speed);
	void setPos(const Vector2D& pos);
	void setMoveTime(float time);
	void set_animation(std::string id);


protected:
	const float SPEED = 5;
protected:
	Timer timer;//单词敲击完以后给予的移动时间

	PlayerId id = PlayerId::None;

	Vector2D pos;
	Vector2D speed;
	bool is_can_move = false;

	bool is_keydown = false;
	int key_code = -1;

	std::unordered_map<std::string, Animation*> animation_pool;
	
	Animation *animation_cur = nullptr;

	Route route;
	StatusMachine status_machine;

	bool is_down_capslock = false;
	bool is_down_shift = false;
};

