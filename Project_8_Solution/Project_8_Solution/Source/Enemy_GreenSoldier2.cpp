#include "Enemy_GreenSoldier2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Enemy.h"

#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_GreenSoldier2::Enemy_GreenSoldier2(int x, int y) : Enemy(x, y)
{
	topAnim.PushBack({ 0,0,32,32 });
	currentAnim = &topAnim;

	botAnim.PushBack({ 160,128,32,32 });
	currentAnim = &botAnim;

	path.PushBack({ 0, -1.0f }, 50, &botAnim);
	path.PushBack({ 0, 1.0f }, 50, &topAnim);


	collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenSoldier2::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Shoot();
	Enemy::Update();
}

void Enemy_GreenSoldier2::Shoot()
{
	if (attackTimer >= 44)
	{
		App->particles->AddParticle(App->particles->enemyBullet, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		attackTimer = 0;
	}

	attackTimer++;
}

void Enemy_GreenSoldier2::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		App->player->score += 100;
	}


}
