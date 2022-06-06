#include "Destruible_Wall.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <math.h>
#include <stdio.h>
#include "SDL/include/SDL_render.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"

Destruible_Wall::Destruible_Wall(int x, int y) : Destruible(x, y)
{

	collider = App->collisions->AddCollider({ 0, 0, 64, 63 }, Collider::Type::DESTRUIBLE, (Module*)App->destruibles);
	tocado = App->textures->Load("Assets/Sprites/Destruible_Wall.png");
	
}

void Destruible_Wall::Update()
{
	Destruible::Update();
}

void Destruible_Wall::Draw()
{
	Destruible::Draw();
	App->render->Blit(tocado, position.x, position.y);
}

void Destruible_Wall::OnCollision(Collider* collider)
{
	if (collider->type != Collider::Type::EXPLOSION)
	{
		return;
	}


	//Aplicar canvio de spritesheet + contador para destruido
	if (collider->type == Collider::Type::EXPLOSION)
	{
		Destroy();
	}

	
}

