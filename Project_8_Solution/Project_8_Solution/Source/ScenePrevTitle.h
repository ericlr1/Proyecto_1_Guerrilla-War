#ifndef __MODULE_PREVSCENETITLE_H__
#define __MODULE_PREVSCENETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ScenePrevTitle : public Module {
public:
	// Constructor
	ScenePrevTitle(bool startEnabled);

	// Destructor
	~ScenePrevTitle();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player, the enemies and the powerups.
	bool CleanUp();

public:
	// Scene duration
	uint duration;

	int scenePart;

	iPoint logo;
	Animation logoAnim;

	iPoint boat;
	Animation boatAnim;

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* introAssets = nullptr;
	SDL_Texture* photoTexture = nullptr;
};

#endif // __MODULE_PREVSCENETITLE_H__
