#include "ScenePrevTitle.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"

ScenePrevTitle::ScenePrevTitle(bool startEnabled) : Module(startEnabled) {}

ScenePrevTitle::~ScenePrevTitle() {}

// Load assets
bool ScenePrevTitle::Start() {
	LOG("Loading background assets");

	bool ret = true;
	
	introAssets = App->textures->Load("Assets/Sprites/intro_assets.png");
	bgTexture = App->textures->Load("Assets/Sprites/title_map_large.png");
	photoTexture = App->textures->Load("Assets/Sprites/pretitle_photo.png");
	

	logoAnim.FullReset();
	logoAnim.PushBack({ 0, 240, 208, 160 });
	logoAnim.loop = false;

	logo.x = (SCREEN_WIDTH / 2);
	logo.y = 20;

	boatAnim.FullReset();
	boatAnim.PushBack({ 0 , 64, 32, 96 });
	boatAnim.PushBack({ 32, 64, 32, 96 });
	boatAnim.PushBack({ 64, 64, 32, 96 });
	boatAnim.PushBack({ 96, 64, 32, 96 });
	boatAnim.loop = true;
	boatAnim.speed = 0.1f;

	boat.x = App->render->GetCameraCenterX();
	boat.y = (SCREEN_HEIGHT / 2) + 64;

	duration = 0;

	scenePart = 0;

	App->render->camera.x = App->render->GetCameraCenterX();
	App->render->camera.y = 0;

	return ret;
}

Update_Status ScenePrevTitle::Update() {
	duration++;

	switch (scenePart) {
	case 0:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN ||
			duration >= SCENE_DURATION / 2) {
			scenePart = 1;
			App->render->camera.x = App->render->GetCameraCenterX();
			App->render->camera.y = 0;
		}
		break;
	case 1:
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN ||
			duration >= SCENE_DURATION) {
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
		App->render->camera.y -= 4 * SCREEN_SIZE;
		boat.y -= 4;
		logo.y -= 4;
		boatAnim.Update();

		break;
	default:
		break;
	}

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_REPEAT) {
		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ScenePrevTitle::PostUpdate() {
	// Draw everything --------------------------------------
	
	

	App->render->Blit(bgTexture, App->render->GetCameraCenterX()/2, SCREEN_HEIGHT - 1904, NULL);

	
	SDL_Rect rect = logoAnim.GetCurrentFrame();
	App->render->Blit(introAssets, logo.x, logo.y, &rect);

	rect = boatAnim.GetCurrentFrame();
	App->render->Blit(introAssets, boat.x, boat.y, &rect);

	App->render->Blit(photoTexture, 0, 0, NULL);


	return Update_Status::UPDATE_CONTINUE;
}

bool ScenePrevTitle::CleanUp() {
	App->textures->Unload(bgTexture);
	bgTexture = nullptr;
	App->textures->Unload(introAssets);
	introAssets = nullptr;
	App->textures->Unload(photoTexture);
	photoTexture = nullptr;

	return true;
}