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
	destructibles = App->textures->Load("Assets/Sprites/Destruibles.png");
	App->audio->PlayMusic("Assets/Fx/Game_sounds_level1.ogg", 1.0f);


	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 280, 2920);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 140, 2820);
	App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 220, 3350);
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 150, 3250);
	App->enemies->AddEnemy(Enemy_Type::TRIPLESHOT, 200, 2700);
	App->render->camera.x = 300;
	App->render->camera.y = 3200;
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
	App->collisions->AddCollider({ 145,2617, 500, 1 }, Collider::Type::RESPAWN_1);
	App->collisions->AddCollider({ 200,1903, 500, 1 }, Collider::Type::RESPAWN_2);
	App->collisions->AddCollider({ 362,1289, 500, 1 }, Collider::Type::RESPAWN_3);
	App->collisions->AddCollider({ 525,916, 500, 1 }, Collider::Type::RESPAWN_4);
	App->collisions->AddCollider({ 458,427, 500, 1 }, Collider::Type::RESPAWN_5);
	
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
	App->collisions->AddCollider({ 534, 1881, 59, 28 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 326, 1881, 61, 28 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 534, 1801, 177, 26 }, Collider::Type::WALL);
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
	App->collisions->AddCollider({ 713, 1342, 27, 636 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 652, 1667, 61, 26 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 207, 1694, 33, 54 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 178, 1345, 31, 634 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 207, 1666, 60, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 208, 1883, 31, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 208, 1803, 31, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 205, 1979, 49, 29 }, Collider::Type::WALL);
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
	App->collisions->AddCollider({ 267, 1482, 41, 162 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 572, 1427, 32, 226 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 480, 1596, 26, 58 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 364, 1596, 26, 58 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 367, 1435, 24, 108 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 480, 1435, 30, 105 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1233, 340, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1287, 141, 55 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1212, 388, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 966, 586, 81 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 944, 570, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 930, 543, 14 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 454, 902, 68, 27 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 617, 1272, 415, 72 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 677, 1246, 359, 26 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 781, 946, 259, 301 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 820, 927, 211, 18 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 845, 900, 62, 26 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 491, 512, 411 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 895, 495, 207, 435 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 385, 1075, 91, 135 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1287, 373, 52 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 202, 303, 359, 178 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 204, 182, 384, 119 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 203, 2, 362, 190 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 565, 2, 89, 162 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 654, 53, 31, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 771, 1, 106, 163 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 834, 164, 199, 73 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 740, 60, 31, 76 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 808, 242, 235, 135 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 812, 400, 244, 77 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 828, 377, 203, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 204, 481, 316, 11 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 844, 479, 186, 18 }, Collider::Type::WALL);


	//Colliders trinchera
	App->collisions->AddCollider({ 130, 2518, 157, 19 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 133, 2579, 2, 2 }, Collider::Type::TRENCH);
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
	App->collisions->AddCollider({ 199, 3328, 89, 14 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 1, 1937, 361, 17 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 557, 1934, 361, 15 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 0, 526, 681, 341 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 745, 526, 290, 341 }, Collider::Type::WATER);

	//Colliders reset anim_water
	
	App->collisions->AddCollider({ 196, 3321, 90, 4 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 186, 3329, 3, 35 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 174, 3366, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 160, 3377, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 150, 3385, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 140, 3394, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 130, 3402, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 120, 3411, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 110, 3420, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 100, 3427, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 76, 3443, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 66, 3464, 4, 34 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 287, 3322, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 298, 3331, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 309, 3336, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 317, 3354, 3, 30 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 331, 3386, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 347, 3404, 3, 36 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 356, 3445, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 375, 3461, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 370, 3445, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 400, 3468, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 384, 3464, 10, 3 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 400, 3479, 3, 14 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 500, 883, 400, 1 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 521, 511, 400, 1 }, Collider::Type::RESET_ANIM_WATER);
	
	//Colliders reset anim_trench
	App->collisions->AddCollider({ 124, 2573, 4, 10 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 127, 2572, 14, 3 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 140, 2575, 3, 7 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 127, 2572, 14, 3 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 127, 2550, 160, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	
	//Armas
	raligun_colldier= App->collisions->AddCollider({ 214, 3106, 32,28 }, Collider::Type::RALIGUN);

	App->collisions->AddCollider({ 250, 3000, 100, 20 }, Collider::Type::DESTRUCTIBLE);
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

	App->render->Blit(destructibles, 163, 113, false);
	
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




