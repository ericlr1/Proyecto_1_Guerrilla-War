#ifndef __ENEMY_HOSTAGE_H__
#define __ENEMY_HOSTAGE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Hostage : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Hostage(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Shoot() override;

	virtual void OnCollision(Collider* collider) override;

private:
	// The path that will define the position in the world
	Path path;

	//Music & FX
	int pickUpFx;
	int deadFx;

	// Enemy animations
	Animation idleAnim, deadAnim, saveAnim;
};

#endif // __ENEMY_GREENSOILDER_H__