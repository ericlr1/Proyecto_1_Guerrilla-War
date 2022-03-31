#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene()
{
	//Map

	mapa = {0, 0, 29, 119};
	
	
	//// ground
	//ground = { 8, 391, 896, 72 };

	//// Background / sky
	//background = { 72, 208, 768, 176 };

	//// Ship
	//ship = { 8, 24, 521, 181 };

	//// Flag animation
	//flag.PushBack({848, 208, 40, 40});
	//flag.PushBack({848, 256, 40, 40});
	//flag.PushBack({848, 304, 40, 40});
	//flag.speed = 0.08f;

	//// Girl animation
	//girl.PushBack({ 624, 16, 32, 56 });
	//girl.PushBack({ 624, 80, 32, 56 });
	//girl.PushBack({ 624, 144, 32, 56 });
	//girl.PushBack({ 624, 80, 32, 56 });
	//girl.speed = 0.08f;
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/GuerrillaWar_1.png");


	return ret;
}

update_status ModuleScene::Update()
{
	/*flag.Update();
	girl.Update();*/

	//UpdateShipPosition();

	return update_status::UPDATE_CONTINUE;
}

//void ModuleScene::UpdateShipPosition()
//{
//	shipMovementTimer++;
//	if (shipMovementTimer > 50)
//	{
//		shipPosition += shipMovement;
//
//		if (shipPosition == -1) shipMovement = -1;
//		if (shipPosition == -5) shipMovement = 1;
//
//		shipMovementTimer = 0;
//	}
//}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	//Draw map
	App->render->Blit(stageTexture, 0, 0, &mapa, 0.75f);

	
	//// Draw everything --------------------------------------
	//App->render->Blit(stageTexture, 0, 0, &background, 0.75f); // sea and sky

	//// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	//App->render->Blit(stageTexture, 0, shipPosition, &ship, 0.85f);

	//App->render->Blit(stageTexture, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	//// TODO 3: Animate the girl on the ship (see sprite sheet)
	//App->render->Blit(stageTexture, 192, 104 + shipPosition, &(girl.GetCurrentFrame()), 0.85f); // flag animation

	//App->render->Blit(stageTexture, 0, 170, &ground);

	return update_status::UPDATE_CONTINUE;
}