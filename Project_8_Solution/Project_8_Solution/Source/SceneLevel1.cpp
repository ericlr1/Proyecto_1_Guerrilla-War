#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 600, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 625, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 640, 80);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 665, 80);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 735, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 750, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 775, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 790, 120);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 830, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 850, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 870, 100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 890, 100);

	App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 300;
	App->render->camera.y = 9300;

	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();

	//Collider camara


	//Colliders pared izquierda
	App->collisions->AddCollider({ 54, 3495, -57, -85 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 88 , 3412, -88, -26 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 109 , 3385, -109, -28 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 144 , 3357, -1146, -81 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 179 , 3277, -181, -28}, Collider::Type::WALL);
	App->collisions->AddCollider({ 201 , 3248, -201, -135 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 174 , 3111, -176, -49 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 156 , 3063, -158, -24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 139 , 3041, -141, -14 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 110 , 3028, -119, -139 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 142 , 2889, -145, -44 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 174 , 2845, -176, -32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200 , 2814, -203, -136 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 175 , 2680, -176, -53 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 142 , 2628, -143, -30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 111 , 2598, -113, -133 }, Collider::Type::WALL);


	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.y += 3;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();

	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}