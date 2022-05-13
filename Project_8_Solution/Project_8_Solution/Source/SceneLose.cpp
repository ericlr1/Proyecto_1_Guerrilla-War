#include "SceneLose.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLevel1.h" 
#include "ModuleFonts.h"
#include "ModulePlayer.h"


SceneLose::SceneLose(bool startEnabled) : Module(startEnabled)
{

}

SceneLose::~SceneLose()
{

}

// Load assets
bool SceneLose::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUV." };
	LoseFont = App->fonts->Load("Assets/Sprites/fonts.png", lookupTable, 2);

	bgTexture = App->textures->Load("Assets/Sprites/loseScreen.png");


	return ret;
}

Update_Status SceneLose::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);


	}
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLose::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->fonts->BlitText(100, 100, LoseFont, "GAME.OVER");
	return Update_Status::UPDATE_CONTINUE;
}