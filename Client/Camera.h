#pragma once
#include "Vector2D.h"
#include "Timer.h"



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
	Vector2D get_size()const { return size; };
	void set_size(const Vector2D& size);

	float get_mulMag()const { return multiple_mag; }//得到放大比
	void mul2();//设置两倍放大
	void mul3();//设置三倍放大
	void set_mulMag(float num);//设置放大比
	void mulX(int x);
	void mulOneThird();
	void mulHalf();
	//抖动
	void shake(double time, int range);

private:
	Timer timer;

	bool is_shaking = false;
	int range = 0;//抖动半径

	float multiple_mag = 1;//放大比

	Vector2D pos;//固定的位置
	Vector2D pos_offset;//偏移位置，用这个
	Vector2D size;
};

