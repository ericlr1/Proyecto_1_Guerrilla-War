#include "Destruible.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"
#include <math.h>


Destruible::Destruible(int x, int y) : position(x, y)
{
	
}

Destruible::~Destruible()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Destruible::GetCollider() const
{
	return collider;
}

void Destruible::Destroy()
{
	needs_to_be_destroyed = true;
}

const bool Destruible::GetNeedsToBeDestroyed()
{
	return needs_to_be_destroyed;
}

void Destruible::Update()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Destruible::Draw()
{
	
}


void Destruible::OnCollision(Collider* collider)
{


	/*App->particles->AddParticle(App->particles->dead, position.x, position.y);
	App->audio->PlayFx(destroyedFx);*/
}