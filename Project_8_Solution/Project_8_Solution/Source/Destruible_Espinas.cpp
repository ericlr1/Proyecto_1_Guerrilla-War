#include "Espinas.h"

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

Destruible_Espinas::Destruible_Espinas(int x, int y) : Destruible(x, y)
{

	collider = App->collisions->AddCollider({ 0, 0, 28, 23 }, Collider::Type::DESTRUIBLE, (Module*)App->destruibles);
	sintocar = App->textures->Load("Assets/Sprites/Espinas.png");


}

void Destruible_Espinas::Update()
{
	Destruible::Update();
}

void Destruible_Espinas::Draw()
{
	Destruible::Draw();
	App->render->Blit(sintocar, position.x, position.y);
}

void Destruible_Espinas::OnCollision(Collider* collider)
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

