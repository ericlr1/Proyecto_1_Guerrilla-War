#pragma once
#ifndef __ENEMY_GRENADES_H__
#define __ENEMY_GRENADES_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Grenades : public Enemy
{
public:
	int cx, cy, rx, ry;

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Grenades(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Draw() override;

	void Shoot() override;

	void Enemy_Grenades::OnCollision(Collider* collider) override;

	//void Draw() override;

private:

	//Tiempo entre disparos
	int attackTimer;


	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation idleAnim;
	Animation death;
};

#endif // __ENEMY_GRENADES_H__