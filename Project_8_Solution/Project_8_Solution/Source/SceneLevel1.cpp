#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

#define SPAWN_MARGIN 60

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
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 290, 3400);


	App->enemies->AddEnemy(Enemy_Type::GREENSOILDER, 280, 3200);

	App->render->camera.x = 300;
	App->render->camera.y = 9200;
	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();

	//Colliders pared izquierda
	collider_wall = App->collisions->AddCollider({ 0, 3411, 48, 89 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3386, 80, 25 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3357, 113, 29 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3273, 140, 84 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3248, 174, 25 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3106, 194, 142 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3065, 176, 41 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3048, 152, 17 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3035, 137, 13 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 3023, 125, 12 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2900, 106, 123 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2847, 138, 53 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2819, 172, 28 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2687, 197, 132 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2638, 180, 49 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2623, 161, 15 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2606, 141, 17 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2589, 121, 17 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2468, 111, 122 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 0, 2438, 142, 29 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 31, 2411, 350, 27 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 31, 2389, 387, 22 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 31, 2261, 408, 128 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 31, 2232, 392, 29 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 121, 2178, 292, 54 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 241, 2153, 152, 25 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 241, 2089, 144, 64 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 241, 1976, 166, 113 }, Collider::Type::WALL);
	//Colliders pared izquierda
	collider_wall = App->collisions->AddCollider({ 427, 3463, 56, 33 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 399, 3413, 84, 50 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 369, 3376, 114, 37 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 340, 3330, 143, 46 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 314, 3302, 169, 28 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 284, 3063, 199, 239 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 298, 3039, 185, 24 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 312, 2901, 170, 138 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 285, 2621, 197, 280 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 386, 2597, 209, 25 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 410, 2569, 193, 27 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 495, 2443, 108, 126 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 525, 2206, 199, 237 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 547, 2143, 177, 63 }, Collider::Type::WALL);
	collider_wall = App->collisions->AddCollider({ 525, 1973, 199, 170 }, Collider::Type::WALL);
	
	
	//Colliders camara
	collider_camera_up = App->collisions->AddCollider({ 0,0, 100,1 }, Collider::Type::CAMERA_UP);
	collider_camera_down = App->collisions->AddCollider({ 0,0, 100,1 }, Collider::Type::CAMERA_DOWN);
	collider_camera_right = App->collisions->AddCollider({ 0,0, 1,100 }, Collider::Type::CAMERA_RIGHT);
	collider_camera_left = App->collisions->AddCollider({ 0,0, 1,100 }, Collider::Type::CAMERA_LEFT);
	
	
	return ret;
}

Update_Status SceneLevel1::Update()
{
	collider_camera_up->SetPos(App->render->camera.x - 150, App->render->camera.y - 6000);
	collider_camera_down->SetPos(App->render->camera.x - 150, App->render->camera.y - 5900);
	collider_camera_right->SetPos(App->render->camera.x - 50, App->render->camera.y - 6000);
	collider_camera_left->SetPos(App->render->camera.x - 150, App->render->camera.y - 6000);

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




