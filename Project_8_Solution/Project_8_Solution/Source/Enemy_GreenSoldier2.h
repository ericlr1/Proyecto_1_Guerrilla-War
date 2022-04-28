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

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation runUpAnim, runDownAnim;
};

#endif // __ENEMY_GREENSOILDER_H__