#ifndef __DESTRUIBLE_H__
#define __DESTRUIBLE_H__
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Destruible
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Destruible(int x, int y);

	// Destructor
	virtual ~Destruible();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	void Destroy();
	const bool GetNeedsToBeDestroyed();


	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

public:
	iPoint position;

	// Sound fx when destroyed
	int destroyedFx = 0;

protected:
	// The enemy's collider
	Collider* collider = nullptr;
	SDL_Texture* texture = nullptr;

private:
	bool needs_to_be_destroyed = false;
};

#endif // __ENEMY_H__