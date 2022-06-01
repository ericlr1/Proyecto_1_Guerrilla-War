
#include "SceneLogo.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneIntro.h" 


SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{

}

SceneLogo::~SceneLogo()
{

}

// Load assets
bool SceneLogo::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/pantllacarga.png");

	return ret;
}

Update_Status SceneLogo::Update()
{


	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);


	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLogo::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}