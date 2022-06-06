#ifndef __DESTRUIBLE_WALL_H__
#define __DESTRUIBLE_WALL_H__

#include "Destruible.h"


class Destruible_Wall : public Destruible
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Destruible_Wall(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Draw() override;

	void Destruible_Wall::OnCollision(Collider* collider) override;

private:
	SDL_Texture* tocado = nullptr;

};

#endif // __ENEMY_GREENSOILDER_H__