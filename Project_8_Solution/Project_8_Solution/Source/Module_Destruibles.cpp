#include "Module_Destruibles.h"

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

Module_Destruibles::Module_Destruibles(bool startEnabled) :Module(startEnabled)
{

}

Module_Destruibles::~Module_Destruibles()
{

}


bool Module_Destruibles::Start()
{
	bool ret = true;
	textura_barricada_horizontal = App->textures->Load("Assets/Sprites/Barricada_Horizontal.png");
	textura_barricada_vertical = App->textures->Load("Assets/Sprites/Barricada_Vertical.png");
	textura_espinas = App->textures->Load("Assets/Sprites/Espinas.png");

	return ret;
}
Update_Status Module_Destruibles::Update()
{
	App->collisions->AddCollider({ 0, 3411, 48, 89 }, Collider::Type::WALL);

	return Update_Status::UPDATE_CONTINUE;
}
Update_Status Module_Destruibles::PostUpdate()
{
	App->render->Blit(textura_barricada_horizontal, 200, 3106, NULL, 1.0, true);
	App->render->Blit(textura_barricada_vertical, 214, 3106, NULL, 1.0, false);
	App->render->Blit(textura_espinas, 214, 3106, NULL, 1.0, false);

	return Update_Status::UPDATE_CONTINUE;
}
void Module_Destruibles::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::DESTRUCTIBLE)
	{
		 
	};
};
