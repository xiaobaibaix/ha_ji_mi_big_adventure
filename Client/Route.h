#pragma once

#include "Vector2D.h"

#include <vector>

class Route
{
public:

	enum class MoveDir {
		Up,
		Down,
		Left,
		Right
	};

	Route();
	~Route()= default;

	void add_idex() { cur_idex++; }
	void add_point(const Vector2D& pos) { point_pool.push_back(pos); }
	void add_point(const std::vector<Vector2D>& pos_pool) { this->point_pool = pos_pool; }
	//�õ���һ��λ��
	Vector2D get_next() { return point_pool[cur_idex +1]; }
	//�õ���ǰҪ�����λ��
	Vector2D get_cur() { return point_pool[cur_idex ]; }
	//������ɶ�
	float get_finish();
	//�õ��ƶ��ķ���
	Vector2D get_move_dir(const Vector2D& pos);
private:
	int cur_idex = 0;

	std::vector<Vector2D> point_pool;

};

