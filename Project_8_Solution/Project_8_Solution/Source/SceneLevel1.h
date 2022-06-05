#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

	enum Suelos
	{
		NONE = -1,
		GROUND,
		WATER,
		TRENCH,


		MAX
	};
	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;


	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	SDL_Texture* destructibles = nullptr;


	Collider* raligun_colldier = nullptr;
	
	// Bools to check if the music has changed
	bool isLevelMusic = false;
	bool isContinueMusic = false;


	//Respawns camera
	bool spawn_1 = false;
	bool spawn_2 = false;
	bool spawn_3 = false;
	bool spawn_4 = false;
	bool spawn_5 = false;

	

};

#endif