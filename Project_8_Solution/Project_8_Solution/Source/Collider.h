#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		WALL_STRAIGHT,
		BODY,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		CAMERA_UP,
		CAMERA_DOWN,
		CAMERA_RIGHT,
		CAMERA_LEFT,

		MAX
	};

	enum class ColliderSide
	{
		UP,
		DOWN,
		RIGHT,	
		LEFT,
	};
	

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);
	
	ColliderSide GetSideToPush(const SDL_Rect& r, int& x, int& y);

	bool Intersects(const SDL_Rect& r) const;

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};


#endif // !__COLLIDER_H__

