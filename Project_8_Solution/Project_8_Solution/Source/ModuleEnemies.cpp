#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"
#include "Enemy_GreenSoldier.h"
#include "Enemy_GreenSoldier2.h"
#include "Enemy_RedSoldier.h"
#include "Enemy_Hostage.h"
#include "Enemy_TripleShot.h"
#include "Enemy_Grenades.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Sprites/Guerrilla War Enemy Spritesheet.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/194.wav");

	return true;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw ();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");
	App->audio->UnloadFx(enemyDestroyedFx);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			App->audio->UnloadFx(enemies[i]->enemyDeadFx);
			App->audio->UnloadFx(enemies[i]->enemyShotFx);
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->GetNeedsToBeDestroyed())
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}

		}
		
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			
			case Enemy_Type::GREENSOLDIER:
				enemies[i] = new Enemy_GreenSoldier(info.x, info.y);
				break;
			case Enemy_Type::GREENSOLDIER2:
				enemies[i] = new Enemy_GreenSoldier2(info.x, info.y);
				break;
			case Enemy_Type::REDSOLDIER:
				enemies[i] = new Enemy_RedSoldier(info.x, info.y);
				break;
			case Enemy_Type::HOSTAGE:
				enemies[i] = new Enemy_Hostage(info.x, info.y);
				break;
			case Enemy_Type::TRIPLESHOT:
				enemies[i] = new Enemy_TripleShot(info.x, info.y);
				break;
			case Enemy_Type::GRENADER:
				enemies[i] = new Enemy_Grenades(info.x, info.y);
				break;
			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}
void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			

			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}