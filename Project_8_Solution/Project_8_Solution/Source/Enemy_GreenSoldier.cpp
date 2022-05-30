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

	death.PushBack({ 0, 320, 32, 64 });
	death.PushBack({ 32, 320, 32, 64 });
	death.PushBack({ 64, 320, 32, 64 });
	death.PushBack({ 96, 320, 32, 64 });
	death.PushBack({ 128, 320, 32, 64 });
	death.PushBack({ 160, 320, 32, 64 });
	death.PushBack({ 192, 320, 32, 64 });
	death.PushBack({ 224, 320, 32, 64 });
	death.PushBack({ 256, 320, 32, 64 });
	death.PushBack({ 288, 320, 32, 64 });
	death.PushBack({ 320, 320, 32, 64 });
	death.PushBack({ 352, 320, 32, 64 });
	death.PushBack({ 384, 320, 32, 64 });
	death.loop = false;
	death.speed = 0.15f;
	death.pingpong = false;



	//collider = App->collisions->AddCollider({100, 0, 30, 55}, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 150, &idleAnim);

	collider = App->collisions->AddCollider({100, 0, 30, 60}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenSoldier::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Shoot();
	Enemy::Update();
}

void Enemy_GreenSoldier::Shoot()
{
	if (attackTimer >=44)
	{
		App->particles->AddParticle(App->particles->enemyBullet, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		attackTimer = 0;
	}

	attackTimer++;
}

void Enemy_GreenSoldier::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		currentAnim = &death;
		App->player->score += 500;
	}


}
