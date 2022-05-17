#include "Enemy_RedSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_render.h"




Enemy_RedSoldier::Enemy_RedSoldier(int x, int y) : Enemy(x, y)
{
	//alpha = 0.0;
	front.PushBack({ 256, 384, 32, 32 });
	frontleft.PushBack({ 288, 384, 32, 32 });
	frontright.PushBack({ 224, 384, 32, 32 });

	front.loop = true;
	front.speed = 0.15f;
	front.pingpong = false;

	path.PushBack({ 0.0f, 0.0f }, 150, &front);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedSoldier::Update()
{
	//alpha = atan2(position.y, position.x);

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
}

void Enemy_RedSoldier::Draw()
{
	//Draw radar
	SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(App->render->renderer, this->position.x, this->position.y, App->player->position.x /** cos(alpha)*/, App->player->position.y /** sin(alpha)*/);
}