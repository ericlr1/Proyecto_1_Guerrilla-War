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
#include "ModuleUI.h"


SceneLose::SceneLose(bool startEnabled) : Module(startEnabled)
{

}

SceneLose::~SceneLose()
{

}

// Load assets
bool SceneLose::Start()
{
	App->audio->Enable();
	LOG("Loading background assets");

	bool ret = true;

	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUV." };
	LoseFont = App->fonts->Load("Assets/Sprites/fonts.png", lookupTable, 2);

	bgTexture = App->textures->Load("Assets/Sprites/loseScreen.png");
	win1 = App->textures->Load("Assets/Sprites/win1.png");
	App->UI->limites = App->textures->Load("Assets/Sprites/limites.png");

	spritesAnimacion = App->textures->Load("Assets/Sprites/animacion_isla.png");
	winAnimation.PushBack({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	//winAnimation.PushBack({224, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT });
	winAnimation.speed = 0.01f;
	winAnimation.loop = true;
	
	

	return ret;
}

Update_Status SceneLose::Update()
{
	bool button_press = false;
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
		if (App->input->controllers[0].buttons[i] == KEY_DOWN)
		{
			button_press = true; break;
		}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || button_press)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 50);


	}

	winAnimation.Update();
	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLose::PostUpdate()
{
	// Draw everything --------------------------------------
	
	SDL_Rect animacion;
	animacion.x = 50;
	animacion.y = 0;
	animacion.w = SCREEN_WIDTH;
	animacion.h = SCREEN_HEIGHT;


	SDL_Rect fondo;
	fondo.x = 50;
	fondo.y = 0;
	fondo.w = SCREEN_WIDTH;
	fondo.h = SCREEN_HEIGHT;
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//Win animation
	if (App->player->lives > 0)
	{
		App->audio->PlayMusic("Assets/Fx/127.ogg");
		App->render->Blit(App->UI->limites, App->render->GetCameraCenterX() - 450, App->render->GetCameraCenterY() - 200, NULL, 1.0, false);
		App->render->Blit(win1, 0, 0, &fondo);
		App->render->Blit(spritesAnimacion, 0, 0, &(winAnimation.GetCurrentFrame())); // Win animation
	}
	else
	{
		//Lose animation (GAME OVER)
		App->render->Blit(bgTexture, 0, 0, &fondo);
		//App->fonts->BlitText(80, 100, LoseFont, "GAME.OVER");
	}

	
	
	return Update_Status::UPDATE_CONTINUE;
}