#ifndef __ENEMY_GREENSOILDER_H__
#define __ENEMY_GREENSOILDER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenSoilder : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_GreenSoilder(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation idleAnim, idlefootAnim;
	Animation deadAnim, deadfootAnim;

	Animation upAnim, downAnim, leftAnim, rightAnim;
	Animation upfootAnim, downfootAnim, leftfootAnim, rightfootAnim;

	Animation leftupAnim, leftdownAnim, rightupAnim, rightdownAnim;
	Animation leftupfootAnim, leftdownfootAnim, rightupfootAnim, rightdownfootAnim;
};

#endif // __ENEMY_GREENSOILDER_H__