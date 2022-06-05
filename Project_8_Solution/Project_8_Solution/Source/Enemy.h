#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

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

	//Calculate enemy rotation with respect to the player
	void lookAtPlayer();

	//The way each enemy shoots, defined by the specific classes
	virtual void Shoot() = 0;

	float AngleToPlayerDegrees();

public:
	// The current position in the world
	iPoint position;
	float alpha = 1;
	float degrees = 0;

	// The distance in pixels to the player
	iPoint distance;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// Sound fx when destroyed
	int enemyDeadFx = 0;
	int enemyShotFx = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
private:
	bool needs_to_be_destroyed = false;
};

#endif // __ENEMY_H__