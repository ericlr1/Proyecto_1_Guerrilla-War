#ifndef __ENEMY_TRIPLESHOT_H__
#define __ENEMY_TRIPLESHOT_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_TripleShot : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_TripleShot(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Shoot() override;

	void Enemy_TripleShot::OnCollision(Collider* collider) override;

	//void Draw() override;

private:

	//Tiempo entre disparos
	int attackTimer;


	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation idleAnim;
};

#endif // __ENEMY_TRIPLESHOT_H__