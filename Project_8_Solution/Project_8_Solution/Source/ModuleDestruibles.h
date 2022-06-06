#ifndef __MODULE_DESTRUIBLE_H__
#define __MODULE_DESTRUIBLE_H__
#include "Module.h"

#define MAX_DESTRUIBLES 200

enum class Destruible_Type
{
	NO_TYPE,
	BARRICADA_H,
	BARRICADA_V,
	ESPINAS,
	WALL,
};

struct DestruibleSpawnpoint
{
	Destruible_Type type = Destruible_Type::NO_TYPE;
	int x, y;
};

class Destruible;
struct SDL_Texture;

class ModuleDestruibles : public Module
{
public:
	// Constructor
	ModuleDestruibles(bool startEnabled);

	// Destructor
	~ModuleDestruibles();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddDestruible(Destruible_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleDestruibleSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleDestruibleDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnDestruible(const DestruibleSpawnpoint& info);

private:
	// A queue with all spawn points information
	DestruibleSpawnpoint spawnQueue[MAX_DESTRUIBLES];

	// All spawned enemies in the scene
	Destruible* destruibles[MAX_DESTRUIBLES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
	int destruibleDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__