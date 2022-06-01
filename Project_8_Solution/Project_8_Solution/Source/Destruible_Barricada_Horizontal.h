#ifndef __DESTRUIBLE_BARRICADA_HORITZONTAL_H__
#define __DESTRUIBLE_BARRICADA_HORITZONTAL_H__

#include "Destruible.h"
 

class Destruible_Barricada_Horizontal : public Destruible
{
public:
	int cx, cy, rx, ry;

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Destruible_Barricada_Horizontal(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Draw() override;

	void Destruible_Barricada_Horizontal::OnCollision(Collider* collider) override;

private:
	SDL_Texture* sintocar = nullptr;
	SDL_Texture* tocado = nullptr;

	Collider* last_collider = nullptr;

};

#endif // __ENEMY_GREENSOILDER_H__