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
#include "ModuleDestruibles.h"
#include "ModuleFonts.h"


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

	App->player->Enable();
	App->enemies->Enable();
	App->destruibles->Enable();
	App->collisions->Enable();
	App->audio->Enable();
	App->fonts->Enable();
	App->particles->Enable();
	App->textures->Enable();

	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	destructibles = App->textures->Load("Assets/Sprites/Destruibles.png");
	App->audio->PlayMusic("Assets/Fx/106.ogg", 1.0f); // bgm Farm

	spawn_1 = false;
	spawn_2 = false;
	spawn_3 = false;
	spawn_4 = false;
	spawn_5 = false;

	//App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 280, 2920);
	//App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 140, 2820);
	//App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 220, 3350);
	//App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 150, 3250);
	//App->enemies->AddEnemy(Enemy_Type::TRIPLESHOT, 200, 2800);

	//CREACION NPCs

	//REHENES [X]
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 140, 2805);
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 175, 2805);

	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 230, 2440);
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 195, 2440);

	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 500, 2110);

	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 490, 1940);
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 395, 1940);

	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 412, 1620);

	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 620, 1105);

	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 680, 835);	
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 710, 835);

	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 695, 600);
	App->enemies->AddEnemy(Enemy_Type::HOSTAGE, 695, 535);

	//REDSOLDIER [X]
	App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 213, 2610);
	
	App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, 400, 1400);

	//TripleShoot
	App->enemies->AddEnemy(Enemy_Type::TRIPLESHOT, 700, 125);

	//GRENADER [X]

	App->enemies->AddEnemy(Enemy_Type::GRENADER, 170, 2970);
	App->enemies->AddEnemy(Enemy_Type::GRENADER, 235, 2970);

	App->enemies->AddEnemy(Enemy_Type::GRENADER, 270, 2440);

	App->enemies->AddEnemy(Enemy_Type::GRENADER, 430, 2150);

	App->enemies->AddEnemy(Enemy_Type::GRENADER, 400, 1470);
	App->enemies->AddEnemy(Enemy_Type::GRENADER, 450, 1470);

	App->enemies->AddEnemy(Enemy_Type::GRENADER, 485, 1110);

	App->enemies->AddEnemy(Enemy_Type::GRENADER, 695, 960);

	App->enemies->AddEnemy(Enemy_Type::GRENADER, 740, 225);
	App->enemies->AddEnemy(Enemy_Type::GRENADER, 600, 225);

	//USSLES [X]

	////Bloc 1
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 240, 2970);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 225, 2970);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 210, 2970);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 240, 3000);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 225, 3000);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 210, 3000);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 240, 3020);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 225, 3020);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 210, 3020);

	////Bloc 2
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 445, 2230);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 460, 2230);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 475, 2230);

	//Bloc 3
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 425, 1290);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 310, 1400);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 335, 1400);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 510, 1400);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, 535, 1400);

	////SHOOTER []

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 155, 2875);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 245, 2875);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 210, 2680);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 240, 2680);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 210, 2720);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 240, 2720);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 245, 2590);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 175, 2590);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 150, 2440);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 320, 2425);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 355, 2445);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 395, 2465);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 430, 2490);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 300, 2445);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 335, 2465);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 375, 2485);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 410, 2510);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 470, 2110);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 410, 2035);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 382, 1860);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 412, 1860);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 442, 1860);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 472, 1860);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 502, 1860);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 375, 1540);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 474, 1540);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 425, 1515);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 425, 1200);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 410, 1195);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 450, 1195);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 520, 1110);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 555, 1110);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 590, 1110);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 535, 1200);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 570, 1200);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 680, 1110);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 715, 1110);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 750, 1110);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 730, 980);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 660, 980);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 630, 1000);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 600, 1020);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 625, 920);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 725, 920);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 615, 400);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 650, 400);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 695, 435);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 740, 400);

	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 602, 185);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 640, 185);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 670, 182);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 740, 185);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 770, 185);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 800, 185);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 770, 210);
	App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, 640, 210);


	



	//Destruibles Horizontal
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 129, 2936);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 158, 2936);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 239, 2936);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 268, 2936);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 279, 2580);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 311, 2580);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 118, 2523);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 149, 2523);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 178, 2523);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 409, 2100);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 438, 2100);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 229, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 258, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 287, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 316, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 345, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 374, 1769);	
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 533, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 562, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 591, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 620, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 649, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 678, 1769);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 400, 1259);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 429, 1259);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 458, 1259);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 480, 1177);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 509, 1177);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 538, 1177);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 567, 1177);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 596, 1177);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 625, 1177);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 600, 895);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 629, 895);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 658, 895);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 735, 895);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 764, 895);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 793, 895);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 600, 462);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 629, 462);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 658, 462);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 735, 462);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 764, 462);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 571, 492);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 658, 492);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, 735, 492);

	//Destruible Vertical
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, 450, 2050);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, 490, 1238);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, 490, 1238);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, 650, 1125);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, 650, 1154);
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, 571, 420);	
	App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, 571, 450);

	//Destructible Espinas
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 425, 2000);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 455, 2000);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 300, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 328, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 356, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 384, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 574, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 546, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 518, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 490, 1666);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 328, 1600);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 546, 1600);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 378, 1572);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 406, 1572);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 406, 1546);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 434, 1572);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 300, 1458);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 300, 1430);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 328, 1458);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 328, 1430);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 328, 1430);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 546, 1300);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 574, 1300);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 546, 890);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 546, 890);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 574, 890);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 574, 862);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 602, 862);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 630, 862);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 658, 862);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 750, 862);
	App->destruibles->AddDestruible(Destruible_Type::ESPINAS, 778, 862);


	//Wall
	App->destruibles->AddDestruible(Destruible_Type::WALL, 212, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 264, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 316, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 368, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 420, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 472, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 524, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 576, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 628, 1694);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 680, 1694);
	
	
	App->destruibles->AddDestruible(Destruible_Type::WALL, 212, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 264, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 316, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 368, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 420, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 472, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 524, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 576, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 628, 1371);
	App->destruibles->AddDestruible(Destruible_Type::WALL, 680, 1371);

	//Setting de la camera
	
	App->player->ammo_raligun = 0;

	// TODO 2: Enable (and properly disable) the player module
	

	//Collider de victoria 
	App->collisions->AddCollider({682, 124, 62, 5}, Collider::Type::WIN);

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
	App->collisions->AddCollider({ 130, 2513, 157, 19 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 130, 2579, 4, 4 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 241, 1748, 164, 18 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 527, 1748, 197, 18 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 404, 1242, 95, 17 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 497, 1161, 154, 21 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 678,975, 91, 14 }, Collider::Type::TRENCH);
	App->collisions->AddCollider({ 638,404,119, 23 }, Collider::Type::TRENCH);

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
	App->collisions->AddCollider({ 199, 3334, 95, 10 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 199, 3323, 89, 14 }, Collider::Type::WATER);
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
	App->collisions->AddCollider({ 368, 1928, 3, 21 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 549, 1928, 3, 21 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 30, 1923, 337, 3 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 559, 1923, 337, 3 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 559, 1960, 337, 3 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 30, 1960, 337, 3 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 682, 521, 3, 353 }, Collider::Type::RESET_ANIM_WATER);
	App->collisions->AddCollider({ 737, 521, 3, 353 }, Collider::Type::RESET_ANIM_WATER);

	//Colliders reset anim_trench
	App->collisions->AddCollider({ 126, 2502, 5, 29 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 287, 2502, 5, 29 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 133, 2499, 148, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 127, 2544, 160, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 123, 2567, 21, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 148, 2572, 3, 20  }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 114, 2572, 3, 12 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 126, 2595, 21, 3 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 221, 1749, 5, 18 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 403, 1749, 5, 18 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 516, 1749, 5, 18 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 701, 1749, 5, 18 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 227, 1747, 172, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 227, 1780, 172, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 520, 1747, 172, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 520, 1780, 172, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 400, 1234, 90, 3 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 400, 1278, 90, 3 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 394, 1238, 3, 33 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 492, 1238, 3, 33 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 489, 1149, 148, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 489, 1200, 148, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 482, 1155, 3, 38 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 649, 1155, 3, 38 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 665, 967, 93, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 665, 1010, 93, 4 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 659, 967, 4, 32 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 761, 967, 4, 32 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 638, 401, 118, 3 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 638, 442, 118, 3 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 628, 403, 3, 40 }, Collider::Type::RESET_ANIM_TRENCH);
	App->collisions->AddCollider({ 760, 403, 3, 40 }, Collider::Type::RESET_ANIM_TRENCH);
	
	//Armas
	raligun_colldier= App->collisions->AddCollider({ 214, 3106, 32,28 }, Collider::Type::RALIGUN);
	return ret;
}

Update_Status SceneLevel1::Update()
{
	if (App->player->lives == 0 && !isLevelMusic) {
		isLevelMusic = true;
		isContinueMusic = false;
		App->audio->PlayMusic("Assets/Fx/124.ogg", 1.0f);
	}

	if (App->player->lives >= 1 && !isContinueMusic) {
		isContinueMusic = true;
		isLevelMusic = false;
		App->audio->PlayMusic("Assets/Fx/106.ogg", 1.0f); // bgm Farm
	}
	
	

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
	App->player->Disable();
	App->enemies->Disable();
	App->destruibles->Disable();
	App->collisions->Disable();
	App->fonts->Disable();
	App->particles->Disable();
	App->textures->Disable();



	return true;
}




