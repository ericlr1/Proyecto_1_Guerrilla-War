#include "ModuleDestruibles.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Destruible.h"

#include "Destruible_Barricada_Vertical.h"
#include "Destruible_Barricada_Horizontal.h"
#include "Espinas.h"
#include "Destruible_Wall.h"

#define SPAWN_MARGIN 50


ModuleDestruibles::ModuleDestruibles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
		destruibles[i] = nullptr;
}

ModuleDestruibles::~ModuleDestruibles()
{

}

bool ModuleDestruibles::Start()
{
	/*texture = App->textures->Load("Assets/Sprites/Guerrilla War Enemy Spritesheet.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/sounds_gwar-195 (1).wav");*/

	return true;
}

Update_Status ModuleDestruibles::Update()
{
	HandleDestruibleSpawn();

	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (destruibles[i] != nullptr)
			destruibles[i]->Update();
	}

	HandleDestruibleDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleDestruibles::PostUpdate()
{
	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (destruibles[i] != nullptr)
			destruibles[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleDestruibles::CleanUp()
{
	LOG("Freeing all destruibles");

	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (destruibles[i] != nullptr)
		{
			delete destruibles[i];
			destruibles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleDestruibles::AddDestruible(Destruible_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (spawnQueue[i].type == Destruible_Type::NO_TYPE)
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

void ModuleDestruibles::HandleDestruibleSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (spawnQueue[i].type != Destruible_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning destruible at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnDestruible(spawnQueue[i]);
				spawnQueue[i].type = Destruible_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleDestruibles::HandleDestruibleDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (destruibles[i] != nullptr)
		{
			if (destruibles[i]->GetNeedsToBeDestroyed())
			{
				delete destruibles[i];
				destruibles[i] = nullptr;
			}
		}
	}
}

void ModuleDestruibles::SpawnDestruible(const DestruibleSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (destruibles[i] == nullptr)
		{
			switch (info.type)
			{
				case Destruible_Type::BARRICADA_V:
					destruibles[i] = new Destruible_Barricada_Vertical(info.x, info.y);
					break;
				case Destruible_Type::BARRICADA_H:
					destruibles[i] = new Destruible_Barricada_Horizontal(info.x, info.y);
					break;
				case Destruible_Type::ESPINAS:
					destruibles[i] = new Destruible_Espinas(info.x, info.y);
					break;
				case Destruible_Type::WALL:
					destruibles[i] = new Destruible_Wall(info.x, info.y);
					break;
			}
			break;
		}
	}
}

void ModuleDestruibles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_DESTRUIBLES; ++i)
	{
		if (destruibles[i] != nullptr && destruibles[i]->GetCollider() == c1)
		{
			destruibles[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}