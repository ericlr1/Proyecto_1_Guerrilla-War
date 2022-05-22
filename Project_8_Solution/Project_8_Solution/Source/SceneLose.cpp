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
	win1 = App->textures->Load("Assets/Sprites/win1.png");

	spritesAnimacion = App->textures->Load("Assets/Sprites/animacion_isla.png");

	//AYUDA
	winAnimation.PushBack({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	winAnimation.PushBack({225, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	winAnimation.speed = 0.01f;
	winAnimation.loop = true;
	
	

	return ret;
}

Update_Status SceneLose::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);


	}

	winAnimation.Update();
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLose::PostUpdate()
{
	// Draw everything --------------------------------------
	
	SDL_Rect animacion;
	animacion.x = 0;
	animacion.y = 0;
	animacion.w = SCREEN_WIDTH;
	animacion.h = SCREEN_HEIGHT;


	SDL_Rect fondo;
	fondo.x = 0;
	fondo.y = 0;
	fondo.w = SCREEN_WIDTH;
	fondo.h = SCREEN_HEIGHT;
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//Win animation
	if (App->player->lives > 0)
	{
		App->render->Blit(win1, 0, 0, &fondo);
		App->render->Blit(spritesAnimacion, 0, 0, &(winAnimation.GetCurrentFrame())); // Win animation
	}
	else
	{
		//Lose animation (GAME OVER)
		App->render->Blit(bgTexture, 0, 0, &fondo);
		App->fonts->BlitText(80, 100, LoseFont, "GAME.OVER");
	}
	
	return Update_Status::UPDATE_CONTINUE;
}