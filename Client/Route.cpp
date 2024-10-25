#include "pch.h"
#include "Route.h"

Route::Route()
{
    point_pool.push_back({ 2040,445 });
    point_pool.push_back({ 2750,445 });
    point_pool.push_back({ 2750,835 });
    point_pool.push_back({ 3145,835 });
    point_pool.push_back({ 3145,1710 });
    point_pool.push_back({ 2120,1710 });
    point_pool.push_back({ 2120,1565 });
    point_pool.push_back({ 845,1565 });
    point_pool.push_back({ 845,845 });
    point_pool.push_back({ 1320,845 });
    point_pool.push_back({ 1320,445 });
    point_pool.push_back({ 2040,445 });
}

float Route::get_finish()
{
    return point_pool.size()==(cur_idex+1);
}

Vector2D Route::get_move_dir(const Vector2D& pos)
{
    return Vector2D(point_pool[cur_idex] - pos).normalize();
}
