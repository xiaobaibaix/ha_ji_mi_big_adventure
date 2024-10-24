#include "pch.h"
#include "Rect.h"

bool Rect::in(const Rect& rect)
{
	bool in_x = !((this->x + this->w) < rect.x || this->x > (rect.x + rect.w));
	bool in_y = !((this->y + this->h) < rect.y || this->y > (rect.y + rect.h));
	return in_x&&in_y;
}
