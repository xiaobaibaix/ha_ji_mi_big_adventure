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

	void add_idex() { cur_idex=(cur_idex+1)% point_pool.size(); }
	void add_point(const Vector2D& pos) { point_pool.push_back(pos); }

	Vector2D get_cur_pos() { return point_pool[cur_idex]; }
	float get_finish();
	Vector2D get_move_dir(const Vector2D& pos);
private:
	int cur_idex = 0;

	std::vector<Vector2D> point_pool;
};

