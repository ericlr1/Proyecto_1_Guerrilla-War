#include "ModuleDestruibles.h"

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

ModuleDestruibles::ModuleDestruibles(bool startEnabled) :Module(startEnabled)
{

}

ModuleDestruibles::~ModuleDestruibles()
{

}


bool ModuleDestruibles::Start()
{
	bool ret = true;
	textura_barricada_horizontal = App->textures->Load("Assets/Sprites/Barricada_Horizontal.png");
	textura_barricada_vertical = App->textures->Load("Assets/Sprites/Barricada_Vertical.png");
	textura_espinas = App->textures->Load("Assets/Sprites/Espinas.png");
	
	App->collisions->AddCollider({ 143, 2951, 34, 23 }, Collider::Type::DESTRUCTIBLE, this);
	
	return ret;
}
Update_Status ModuleDestruibles::Update()
{
	

	return Update_Status::UPDATE_CONTINUE;
}
Update_Status ModuleDestruibles::PostUpdate()
{
	App->render->Blit(textura_barricada_horizontal, 143, 2951, NULL, 1.0, true);
	App->render->Blit(textura_barricada_vertical, 214, 3106, NULL, 1.0, false);
	App->render->Blit(textura_espinas, 214, 3106, NULL, 1.0, false);

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleDestruibles::OnCollision(Collider* c1, Collider* c2)
{

}
