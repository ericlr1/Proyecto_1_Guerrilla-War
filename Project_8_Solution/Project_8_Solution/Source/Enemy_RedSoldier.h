#ifndef __ENEMY_REDSOLDIER_H__
#define __ENEMY_REDSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedSoldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_RedSoldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void Shoot() override;
	void Draw() override;
	void Enemy_RedSoldier::OnCollision(Collider* collider) override;

public:

	float alpha;	//angle computed as atan2

	//Tiempo entre disparos
	int attackTimer;

	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation front, frontleft, frontright;
};

#endif // __ENEMY_REDSOLDIER_H__