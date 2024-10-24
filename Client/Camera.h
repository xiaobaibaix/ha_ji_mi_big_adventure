#pragma once
#include "Vector2D.h"
#include "Timer.h"
#include "Rect.h"


class Camera
{
public:
	Camera(const Vector2D& pos,const Vector2D& size);
	~Camera();

	void on_input(const SDL_Event* event);

	void on_update(double delta_time);
	//移动到pos位置
	void move_to(const Vector2D& pos);
	//移动delta距离
	void move_dalta(const Vector2D& delta_distance);

	Vector2D get_pos()const { return pos_offset; }
	Vector2D get_size()const { return viewport.get_size(); };
	void set_size(const Vector2D& size);

	float get_mulMag()const { return multiple_mag; }//得到放大比
	void set_mulMag(float num);//设置放大比
	void mulX(float x);//缩放多少倍
	//抖动
	void shake(double time, int range);

private:
	Timer timer;

	bool is_shaking = false;
	int range = 0;//抖动半径

	float multiple_mag = 1;//放大比

	Rect viewport = { 0,0,640,480 };
	Vector2D pos_offset = {0,0};//偏移位置
	
	Vector2D pos_mouse = {0,0};//鼠标的位置
	float mouse_move_coefficient = 2;//鼠标拖动灵敏系数
	
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
	bool is_move_mouse_mid = false;

	Rect sence_area = { 0,0,3840,2160 };
};

