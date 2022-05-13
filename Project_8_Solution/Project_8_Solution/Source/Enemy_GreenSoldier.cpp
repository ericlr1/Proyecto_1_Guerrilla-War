#include "Enemy_GreenSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <math.h>
#include <stdio.h>
#include "SDL/include/SDL_render.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Enemy_GreenSoldier::Enemy_GreenSoldier(int x, int y) : Enemy(x, y)
{

	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 416, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 416, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.loop = true;
	idleAnim.speed = 0.15f;
	idleAnim.pingpong = false;

	collider = App->collisions->AddCollider({100, 0, 30, 55}, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 150, &idleAnim);

	collider = App->collisions->AddCollider({100, 0, 30, 60}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenSoldier::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Shoot();
	//cx = 225 / 2;
	//cy = 325 / 2;

	//rx = App->player->position.x - cx;
	//ry = -(App->player->position.y - cy);
	//alpha = atan2(ry, rx);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

//void Enemy_GreenSoldier::Draw()
//{
//	degrees = alpha / (M_PI / 180.0);
//	if (degrees < 0)	degrees += 360.0f;
//
//	//Draw radar
//	SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, 255);
//	SDL_RenderDrawLine(App->render->renderer, cx, cy, cx + cy * cos(alpha), cy - cy * sin(alpha));
//
//	//Update screen
//	SDL_RenderPresent(App->render->renderer);
//}

void Enemy_GreenSoldier::Shoot()
{
	if (attackTimer >= 50)
	{
		App->particles->AddParticle(App->particles->enemyBullet, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		attackTimer = 0;
	}

	attackTimer++;
}
