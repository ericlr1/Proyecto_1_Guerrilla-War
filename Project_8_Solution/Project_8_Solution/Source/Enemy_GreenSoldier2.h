#ifndef __ENEMY_GREENSOLDIER2_H__
#define __ENEMY_GREENSOLDIER2_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenSoldier2 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_GreenSoldier2(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Shoot() override;

private:
	// The path that will define the position in the world
	Path path;

	int shootdelay;

	enum Directions {
		UP, DOWN, RIGHT,
		LEFT, UP_RIGHT, UP_LEFT,
		DOWN_RIGHT, DOWN_LEFT
	};

	Directions looking;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	// Enemy animations
	Animation topAnim;
	Animation botAnim;

	Animation topUp;
	Animation botUp;

	Animation topUpRight;
	Animation botUpRight;

	Animation topRight;
	Animation botRight;

	Animation topDownRight;
	Animation botDownRight;

	Animation topDown;
	Animation botDown;

	Animation topDownLeft;
	Animation botDownLeft;

	Animation topLeft;
	Animation botLeft;

	Animation topUpLeft;
	Animation botUpLeft;
};

#endif // __ENEMY_GREENSOILDER_H__