#pragma once

#include "Route.h"
#include "Animation.h"
#include "StatusMachine.h"

#include <unordered_map>
#include <Queue>

class Player
{
public:
	enum class PlayerId {
		None,
		Self,
		Other
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
	char pressed_key_code();
	bool can_move();
	Vector2D get_move_dir();
	StatusMachine* get_statusMachine();
	const Vector2D& get_size()const;

	void setSpeed(const Vector2D& speed);
	void setPos(const Vector2D& pos);
	void setMoveTime(float time);
	void addMoveTime(float time);
	void set_animation(std::string id);
	void set_size(const Vector2D& size);


protected:
	char get_press_key_code();

	const float SPEED = 50;
protected:
	Timer timer;//单词敲击完以后给予的移动时间

	float t = 0;//添加的时间

	PlayerId id = PlayerId::None;

	Vector2D pos;
	Vector2D speed;
	Vector2D size;
	Vector2D dir;

	bool is_can_move = false;


	bool is_keydown = false;
	int key_code = -1;

	std::unordered_map<std::string, Animation*> animation_pool;
	std::queue<char> key_code_pool;

	Animation *animation_cur = nullptr;

	Route route;

	StatusMachine status_machine;

	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;

	bool is_down_capslock = false;
	bool is_down_shift = false;
};

