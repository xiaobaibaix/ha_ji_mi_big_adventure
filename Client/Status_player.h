#pragma once
#include "Animation.h"

class Player;

class Status {
public:
	Status(Player* player);
	~Status() = default;

	virtual void on_enter() {};
	virtual void on_update(double delta_time) {};
	virtual void on_exit() {};

protected:
	Player* player = nullptr;
};

//------------------------------------------
//ø’œ–
class IdleLeft:public Status
{
public:
	IdleLeft(Player* player);
	~IdleLeft()=default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;

};

class IdleRight :public Status
{
public:
	IdleRight(Player* player);
	~IdleRight() = default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;
};

class IdleUp :public Status
{
public:
	IdleUp(Player* player);
	~IdleUp() = default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;
};

class IdleDown :public Status
{
public:
	IdleDown(Player* player);
	~IdleDown() = default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;
};

//---------------------------------------------
//±º≈‹
class RunLeft :public Status
{
public:
	RunLeft(Player* player);
	~RunLeft() = default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;
};

class RunRight :public Status
{
public:
	RunRight(Player* player);
	~RunRight() = default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;
};

class RunUp :public Status
{
public:
	RunUp(Player* player);
	~RunUp() = default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;
};

class RunDown :public Status
{
public:
	RunDown(Player* player);
	~RunDown() = default;

	void on_enter()override;
	void on_exit()override;

	void on_update(double delta_time)override;
};