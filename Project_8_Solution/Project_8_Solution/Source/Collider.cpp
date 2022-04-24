#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener): rect(rectangle), type(type), listener(listener)
{

}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

Collider::ColliderSide Collider::GetSideToPush(const SDL_Rect& r, int& x, int& y)
{
	x = 0;
	y = 0;

	int rightside = r.w + r.x - rect.x;
	int leftside = rect.x + rect.w - r.x;
	int upside = r.y + r.h - rect.y;
	int downside = rect.h + rect.y - r.y;

	if (rightside > 0)
	{
		if (leftside < 0 || rightside < leftside)
		{
			if (upside < 0 || rightside < upside)
			{
				if (downside < 0 || rightside < downside)
				{
					x = rightside;
					return ColliderSide::RIGHT;
				}
			}
		}
	}

	if (leftside > 0)
	{
		if (rightside < 0 || leftside < rightside)
		{
			if (upside < 0 || leftside < upside)
			{
				if (downside < 0 || leftside < downside)
				{
					x = -leftside;
					return ColliderSide::LEFT;
				}
			}
		}
	}

	if (upside > 0)
	{
		if (rightside < 0 || upside < rightside)
		{
			if (leftside < 0 || upside < leftside)
			{
				if (downside < 0 || upside < downside)
				{
					y = upside;
					return ColliderSide::UP;
				}
			}
		}
	}

	if (downside > 0)
	{
		if (rightside < 0 || downside < rightside)
		{
			if (leftside < 0 || downside < leftside)
			{
				if (downside < 0 || downside < upside)
				{
					y = -downside;
					return ColliderSide::DOWN;
				}
			}
		}
	}

	return ColliderSide::RIGHT;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}