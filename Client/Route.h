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
	//得到下一个位置
	Vector2D get_next() { return point_pool[cur_idex +1]; }
	//得到当前要到达的位置
	Vector2D get_cur() { return point_pool[cur_idex ]; }
	//返回完成度
	float get_finish();
	//得到移动的方向
	Vector2D get_move_dir(const Vector2D& pos);
private:
	int cur_idex = 0;

	std::vector<Vector2D> point_pool;

};

