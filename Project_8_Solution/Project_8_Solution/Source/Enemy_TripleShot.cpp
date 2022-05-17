#include "Enemy_TripleShot.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <math.h>
#include <stdio.h>
#include "SDL/include/SDL_render.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Enemy.h"
#include "ModulePlayer.h"

Enemy_TripleShot::Enemy_TripleShot(int x, int y) : Enemy(x, y)
{
	Enemy_TripleShot:attackTimer = 0;

	idleAnim.PushBack({ 416, 352, 32, 64 });
	idleAnim.PushBack({ 416, 352, 32, 64 });
	idleAnim.PushBack({ 416, 352, 32, 64 });
	idleAnim.PushBack({ 448, 352, 32, 64 });
	idleAnim.PushBack({ 480, 352, 32, 64 });
	idleAnim.PushBack({ 512, 352, 32, 64 });
	idleAnim.PushBack({ 480, 352, 32, 64 });
	idleAnim.PushBack({ 512, 352, 32, 64 });
	idleAnim.PushBack({ 448, 352, 32, 64 });

	currentAnim = &idleAnim;

	collider = App->collisions->AddCollider({ 100, 0, 30, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 160, &idleAnim);
}

void Enemy_TripleShot::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Shoot();
	
	Enemy::Update();
}



void Enemy_TripleShot::Shoot()
{
	if (attackTimer >= 50)
	{
		App->particles->AddParticle(App->particles->enemyBullet, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemyBulletDL, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemyBulletDR, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		attackTimer = 0;
	}

	attackTimer++;
}

void Enemy_TripleShot::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		App->player->score += 500;
	}


}
