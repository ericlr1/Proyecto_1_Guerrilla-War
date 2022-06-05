#ifndef __DESTRUIBLE_ESPINAS_H__
#define __DESTRUIBLE_ESPINAS_H__

#include "Destruible.h"


class Destruible_Espinas : public Destruible
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Destruible_Espinas(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void Draw() override;

	void Destruible_Espinas::OnCollision(Collider* collider) override;

private:
	SDL_Texture* sintocar = nullptr;
	

};

#endif // __ENEMY_GREENSOILDER_H__