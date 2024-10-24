#pragma once
#include "Vector2D.h"

class Rect
{
public:
	Rect(float x, float y, float w, float h) :x(x),y(y),w(w),h(h){};
	~Rect()=default;

	void move_to(const Vector2D& pos) { this->x = pos.x, y = pos.y; }
	void move_to_x(float x) { this->x = x; }
	void move_to_y(float y) { this->y = y; }
	void move_delta(const Vector2D& delta_distance) { x += delta_distance.x, y += delta_distance.y; }

	void set_size(const Vector2D& size) { w = size.x, h = size.y; }

	Vector2D get_pos()const { return Vector2D(x, y); }
	Vector2D get_size()const { return Vector2D(w, h); }
	//左上
	Vector2D get_pos_lu()const { return Vector2D(x, y); }
	//左下
	Vector2D get_pos_ld()const { return Vector2D(x, y+h); }
	//右上
	Vector2D get_pos_ru()const { return Vector2D(x+w, y); }
	//右下
	Vector2D get_pos_rd()const { return Vector2D(x+w, y+h); }
	//中心
	Vector2D get_pos_ct()const { return Vector2D((x+w)/2, (y+h)/2); }
	//矩形是否在里面
	bool in(const Rect& rect);

private:
	float x, y;
	float w, h;
};

