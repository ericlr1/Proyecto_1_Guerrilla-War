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
		BODY,
		FOOT,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		WATER,
		TRENCH,
		HOSTAGE,
		RALIGUN,
		RALIGUN_SHOOT,
		EXPLOSION,
		DESTRUIBLE,
		RESET_ANIM_WATER,
		RESET_ANIM_TRENCH,
		WIN,
		RESPAWN_1,
		RESPAWN_2,
		RESPAWN_3,
		RESPAWN_4,
		RESPAWN_5,
		
	


		MAX
	};

	enum class ColliderSide
	{
		UP,
		DOWN,
		RIGHT,	
		LEFT,
	};
	enum Respawn
	{
		

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

