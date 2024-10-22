#include "pch.h"
#include "Camera.h"

#include <random>

Camera::Camera(const Vector2D& pos, const Vector2D& size):pos(pos),pos_offset(pos),size(size)
{
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			is_shaking = false;
		}
	);
	timer.pause();
}

Camera::~Camera()
{
}

void Camera::on_input(const SDL_Event* event)
{
}

void Camera::on_update(double delta_time)
{
	timer.on_update((float)delta_time);
	
	if (!is_shaking)return;

	// 创建随机数生成器
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, range);

	int random_dis_delta = dis(gen);

	std::uniform_int_distribution<> thta(0, 360);

	int random_thta_delta = thta(gen);

	float random_x = random_dis_delta * cos(random_thta_delta * M_PI / 180);
	float random_y = random_dis_delta * sin(random_thta_delta * M_PI / 180);
	
	pos_offset.x = pos.x+random_x;
	pos_offset.y = pos.y+random_y;

	//比例
	size *= multiple_mag;

}

void Camera::move_to(const Vector2D& pos)
{
	this->pos = pos;
	this->pos_offset = pos;
}

void Camera::move_dalta(const Vector2D& delta_distance)
{
	this->pos += delta_distance;
	this->pos_offset += delta_distance;
}
//得到放大比
void Camera::set_size(const Vector2D& size)
{
	this->size = size;
}

//设置两倍放大
void Camera::mul2() { 
	mulX(2);

}

//设置三倍放大
void Camera::mul3() { 
	mulX(3);
}

//设置半倍放大
void Camera::mulHalf() {
	mulX(1 / 2);

}

//设置三分之一倍放大
void Camera::mulOneThird() {
	mulX(1 / 3.0);
}


void Camera::set_mulMag(float num) { 
	multiple_mag = num; 
}

void Camera::mulX(int x)
{
	multiple_mag *= x;
	float offset_x = (size.x * multiple_mag - size.x) / 2;
	float offset_y = (size.y * multiple_mag - size.y) / 2; 

	pos.x -= offset_x;
	pos.y -= offset_y;
	
	pos_offset.x -= offset_x;
	pos_offset.y -= offset_y;
}

void Camera::shake(double time, int range)
{
	this->range = range;
	timer.set_wait_time((float)time);
	timer.restart();
}
