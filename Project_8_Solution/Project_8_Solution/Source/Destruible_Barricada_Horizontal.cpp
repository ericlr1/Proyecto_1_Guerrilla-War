#include "Destruible_Barricada_Horizontal.h"

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

Destruible_Barricada_Horizontal::Destruible_Barricada_Horizontal(int x, int y) : Destruible(x, y)
{

	collider = App->collisions->AddCollider({ 0, 0, 39, 26 }, Collider::Type::DESTRUIBLE, (Module*)App->destruibles);
	sintocar = App->textures->Load("Assets/Sprites/Barricada_Horitzontal.png");
	tocado = App->textures->Load("Assets/Sprites/Barricada_Vertical.png");
	
	texture = sintocar;
	
}

void Destruible_Barricada_Horizontal::Update()
{
	Destruible::Update();
}

void Destruible_Barricada_Horizontal::Draw()
{
	Destruible::Draw();
	App->render->Blit(texture, position.x, position.y);
}

void Destruible_Barricada_Horizontal::OnCollision(Collider* collider)
{
	//Aplicar canvio de spritesheet + contador para destruido
	if (collider->type == Collider::Type::EXPLOSION)
	{
		texture = tocado;
		Destroy();
	}
}
