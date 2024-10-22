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
	//�ƶ���posλ��
	void move_to(const Vector2D& pos);
	//�ƶ�delta����
	void move_dalta(const Vector2D& delta_distance);

	Vector2D get_pos()const { return pos_offset; }
	Vector2D get_size()const { return size; };
	void set_size(const Vector2D& size);

	float get_mulMag()const { return multiple_mag; }//�õ��Ŵ��
	void mul2();//���������Ŵ�
	void mul3();//���������Ŵ�
	void set_mulMag(float num);//���÷Ŵ��
	void mulX(int x);
	void mulOneThird();
	void mulHalf();
	//����
	void shake(double time, int range);

private:
	Timer timer;

	bool is_shaking = false;
	int range = 0;//�����뾶

	float multiple_mag = 1;//�Ŵ��

	Vector2D pos;//�̶���λ��
	Vector2D pos_offset;//ƫ��λ�ã������
	Vector2D size;
};

