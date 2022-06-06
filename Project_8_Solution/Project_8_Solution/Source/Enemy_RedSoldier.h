#ifndef __ENEMY_REDSOLDIER_H__
#define __ENEMY_REDSOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_RedSoldier : public Enemy
{
public:
	int cx, cy, rx, ry;

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_RedSoldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Draw() override;

	void Shoot() override;

	void Enemy_RedSoldier::OnCollision(Collider* collider) override;

	//void Draw() override;

private:

	//Tiempo entre disparos
	int attackTimer;


	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation RedSloideridleAnim;
	Animation RedSloiderleftAnim;
	Animation RedSloiderrightAnim;
	Animation RedSloiderbackAnim;
	Animation death;
};

#endif // __ENEMY_REDSOLDIER_H__
