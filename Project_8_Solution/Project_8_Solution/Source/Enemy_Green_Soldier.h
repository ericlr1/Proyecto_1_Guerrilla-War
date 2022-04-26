#ifndef __ENEMY_GREEN_SOLDIER_H__
#define __ENEMY_GREEN_SOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Green_Soldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Green_Soldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation front, back;
};

#endif // __ENEMY_MECH_H__