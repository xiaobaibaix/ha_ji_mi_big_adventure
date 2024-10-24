#include "pch.h"
#include "Camera.h"

#include <random>

Camera::Camera(const Vector2D& pos, const Vector2D& size):viewport(pos.x,pos.y,size.x,size.y),pos_offset(pos)
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
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_UP) {
			// ���Ϸ����������
			is_move_up = true;
		}
		else if (event->key.keysym.sym == SDLK_DOWN) {
			// ���·����������
			is_move_down = true;
		}
		else if (event->key.keysym.sym == SDLK_LEFT) {
			// �������������
			is_move_left = true;
		}
		else if (event->key.keysym.sym == SDLK_RIGHT) {
			// ���ҷ����������
			is_move_right = true;
		}
		break;
	case SDL_KEYUP:
		if (event->key.keysym.sym == SDLK_UP) {
			// ���Ϸ�������ͷ�
			is_move_up = false;
		}
		else if (event->key.keysym.sym == SDLK_DOWN) {
			// ���·�������ͷ�
			is_move_down = false;
		}
		else if (event->key.keysym.sym == SDLK_LEFT) {
			// ����������ͷ�
			is_move_left = false;
		}
		else if (event->key.keysym.sym == SDLK_RIGHT) {
			// ���ҷ�������ͷ�
			is_move_right = false;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_MIDDLE) {
			// ����м�������
			is_move_mouse_mid = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event->button.button == SDL_BUTTON_MIDDLE) {
			// ����м����ͷ�
			is_move_mouse_mid = false;
		}
		break;
	case SDL_MOUSEMOTION://����ƶ�
		if (is_move_mouse_mid)move_dalta(Vector2D( pos_mouse.x-(float)event->motion.x ,pos_mouse.y-(float)event->motion.y) * mouse_move_coefficient);

		pos_mouse.x = (float)event->motion.x;
		pos_mouse.y = (float)event->motion.y;
		break;
	case SDL_MOUSEWHEEL: {
		// ��ȡ�������¼�������
		const SDL_MouseWheelEvent* wheelEvent = &event->wheel;
		// wheelEvent->x �� wheelEvent->y ������������
		// wheelEvent->direction ָʾ�����ķ���
		// wheelEvent->mouse_x �� wheelEvent->mouse_y ��������ڹ���ʱ��λ��
		float x = (float)wheelEvent->x;
		float y = (float)wheelEvent->y;
		Uint32 direction = wheelEvent->direction;
		float mouseX = wheelEvent->preciseX;
		float mouseY = wheelEvent->preciseY;

		// ���ݹ�������ִ�в���
		if (direction == SDL_MOUSEWHEEL_NORMAL) {
			if (y > 0) {
				// ���Ϲ���
				std::cout << "mouse whell up!" << std::endl;
				set_mulMag(get_mulMag() - 0.1f);
			}
			else {
				// ���¹���
				std::cout << "mouse whell down!" << std::endl;
				set_mulMag(get_mulMag() + 0.1f);
			}
		}
		else if (direction == SDL_MOUSEWHEEL_FLIPPED) {
			// �������򱻷�ת
		}
		break;
	}
	}
}

void Camera::on_update(double delta_time)
{
	timer.on_update((float)delta_time);
	//std::cout << viewport.get_pos();
	//std::cout << "rota:" << viewport.get_size().get_ratio() << std::endl;

	if (is_shaking) {
		// ���������������
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, range);

		int random_dis_delta = dis(gen);

		std::uniform_int_distribution<> thta(0, 360);

		int random_thta_delta = thta(gen);

		float random_x = (float)(random_dis_delta * cos(random_thta_delta * M_PI / 180));
		float random_y = (float)(random_dis_delta * sin(random_thta_delta * M_PI / 180));

		pos_offset.x = viewport.get_pos().x + random_x;
		pos_offset.y = viewport.get_pos().y + random_y;
	}

	if (is_move_up)move_dalta({ 0,-5 });
	if (is_move_down)move_dalta({ 0,5 });
	if (is_move_left)move_dalta({ -5,0 });
	if (is_move_right)move_dalta({ 5,0 });

}

void Camera::move_to(const Vector2D& pos)
{
	viewport.move_to(pos);
	this->pos_offset = pos;
}

void Camera::move_dalta(const Vector2D& delta_distance)
{
	viewport.move_delta({ delta_distance.x,delta_distance.y });

	if (viewport.get_pos().x < sence_area.get_pos().x)
		viewport.move_delta({ sence_area.get_pos().x - viewport.get_pos().x,0 });
	if(viewport.get_pos_rd().x > sence_area.get_pos_rd().x)
		viewport.move_delta({ sence_area.get_pos_rd().x - viewport.get_pos_rd().x,0 });
	if (viewport.get_pos().y < sence_area.get_pos().y)
		viewport.move_delta({ 0,sence_area.get_pos().y - viewport.get_pos().y });
	if(viewport.get_pos_rd().y > sence_area.get_pos_rd().y)
		viewport.move_delta({0,sence_area.get_pos_rd().y - viewport.get_pos_rd().y });
	
	this->pos_offset = viewport.get_pos();
}
//�õ��Ŵ��
void Camera::set_size(const Vector2D& size)
{
	viewport.set_size(size);
}

void Camera::set_mulMag(float num) { 
	float compare = num / multiple_mag;
	mulX(compare);
}

void Camera::mulX(float x)
{
	if (multiple_mag <= 1)
		multiple_mag = multiple_mag * x <= 0.25 ? 0.25f : multiple_mag * x;
	else
		multiple_mag = (multiple_mag * x >= sence_area.get_size().y / 480)  ? (sence_area.get_size().y / 480) : multiple_mag * x;
	float offset_x = (640 * multiple_mag - viewport.get_size().x) / 2;
	float offset_y = (480 * multiple_mag- viewport.get_size().y) / 2;

	move_dalta({-offset_x ,-offset_y });

	viewport.set_size(Vector2D(640,480)*multiple_mag);

}

void Camera::shake(double time, int range)
{
	this->range = range;
	timer.set_wait_time((float)time);
	timer.restart();
}
