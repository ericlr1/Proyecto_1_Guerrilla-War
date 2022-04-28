#ifndef __SCENE_LOGO_H__
#define __SCENE_LOGO_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
struct SDL_Texture;

class SceneLogo : public Module
{
public:
	//Constructor
	SceneLogo(bool startEnabled);

	//Destructor
	~SceneLogo();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	
};

#endif