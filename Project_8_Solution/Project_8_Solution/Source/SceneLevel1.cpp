#include "SceneLevel1.h"

#include "Collider.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include <SDL/include/SDL_scancode.h>
#include "ModuleInput.h"
#include "Enemy_GreenSoldier.h"
#include "Enemy_GreenSoldier2.h"

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
	App->audio->PlayMusic("Assets/Fx/Game_sounds_level1.ogg", 1.0f);


	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 280, 2920);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 140, 2820);
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 200, 2820);
	App->render->camera.x = 300;
	App->render->camera.y = 9200;
	// TODO 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->particles->Enable();

	//Colliders pared izquierda
	App->collisions->AddCollider({ 0, 3411, 48, 89 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3386, 80, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3357, 113, 29 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3273, 140, 84 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3248, 174, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3106, 194, 142 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3065, 176, 41 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3048, 152, 17 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3035, 137, 13 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3023, 125, 12 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2900, 106, 123 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2847, 138, 53 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2819, 172, 28 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2687, 197, 132 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2638, 180, 49 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2623, 161, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2606, 141, 17 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2589, 121, 17 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2468, 111, 122 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 2438, 142, 29 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 31, 2411, 350, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 31, 2389, 387, 22 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 31, 2261, 408, 128 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 31, 2232, 392, 29 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 121, 2178, 292, 54 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 241, 2153, 152, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 241, 2089, 144, 64 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 241, 1976, 166, 113 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 3510, 500, 2 }, Collider::Type::WALL);

	//Respawns
	App->collisions->AddCollider({ 234,1903, 485, 16 }, Collider::Type::RESPAWN);
	App->collisions->AddCollider({ 551,489, 280, 24 }, Collider::Type::RESPAWN);
	
	

	
	

	//Colliders pared izquierda
	App->collisions->AddCollider({ 427, 3463, 56, 33 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 399, 3413, 84, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 369, 3376, 114, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340, 3330, 143, 46 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 314, 3302, 169, 28 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 284, 3063, 199, 239 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 298, 3039, 185, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 312, 2901, 170, 138 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 285, 2621, 197, 280 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 386, 2597, 209, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, 2569, 193, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 495, 2443, 108, 126 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 525, 2206, 199, 237 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 547, 2143, 177, 63 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 525, 1973, 199, 170 }, Collider::Type::WALL);
	
	//Colliders dentro del mapa
	App->collisions->AddCollider({ 237, 1802, 150, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 534, 1802, 150, 150 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 326, 1881, 61, 28 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 534, 1881, 61, 28 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 237, 1640, 60, 54 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 237, 1478, 30, 162 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 237, 1425, 59, 53 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 237, 1344, 90, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 314, 3302, 60, 54 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 593, 1640, 61, 54 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 623, 1425, 30, 215 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 654, 1667, 71, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 623, 1344, 179, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 474, 1075, 120, 55 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 564, 1049, 29, 27 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 245, 1698, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 301, 1698, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 361, 1698, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 420, 1698, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 479, 1698, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 540, 1698, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 598, 1698, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 658, 1698, 17, 50 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 243, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 302, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 362, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 393, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 480, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 540, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 600, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 660, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 718, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 778, 1375, 17, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 835, 1375, 17, 50 }, Collider::Type::WALL);





	//Colliders trinchera
	App->collisions->AddCollider({ 130, 2574, 10, 5 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 133, 2502, 150, 25 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 241, 1748, 164, 18 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 527, 1748, 197, 18 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 404, 1242, 95, 17 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 497, 1161, 154, 21 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 678,975, 91, 14 }, Collider::Type::TRENCH);

	// Colliders agua
	App->collisions->AddCollider({ 78, 3472, 315, 37 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 82, 3456, 290, 16 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 102, 3439, 248, 17 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 116, 3429, 233, 10 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 129, 3413, 216, 16 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 146, 3406, 195, 7 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 155, 3398, 174, 8 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 164, 3386, 157, 12 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 175, 3376, 139, 10 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 189, 3359, 125, 17 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 197, 3349, 111, 10 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 199, 3339, 95, 10 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 199, 3325, 89, 14 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 241, 1926, 131, 19 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 565, 1928, 160, 19 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 453, 526, 490, 346 }, Collider::Type::WATER);

	


	//Armas
	App->collisions->AddCollider({ 214, 3106, 32,28 }, Collider::Type::RALIGUN);

	return ret;
}

Update_Status SceneLevel1::Update()
{
	
	
	

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
	App->collisions->Disable();
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}




