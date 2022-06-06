#include "Enemy_GreenSoldier2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Enemy.h"

#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Enemy_GreenSoldier2::Enemy_GreenSoldier2(int x, int y) : Enemy(x, y)
{

	downAnim.PushBack({ 416, 64, 32, 64 });
	downAnim.PushBack({ 384, 64, 32, 64 });
	downAnim.PushBack({ 384, 0, 32, 64 });
	downAnim.PushBack({ 384, 128, 32, 64 });
	downAnim.PushBack({ 384, 0, 32, 64 });
	downAnim.PushBack({ 384, 64, 32, 64 });

	downAnim.speed = 0.15;
	downAnim.pingpong = false;
	currentAnim = &downAnim;

	idleAnim.PushBack({ 448, 0, 32, 64});

	upAnim.PushBack({ 384, 192, 32, 64 });
	upAnim.PushBack({ 416, 192, 32, 64 });
	upAnim.PushBack({ 448, 192,  32, 64 });
	upAnim.PushBack({ 416, 192,  32, 64 });
	upAnim.PushBack({ 384, 192,  32, 64 });
	upAnim.PushBack({ 448, 128,  32, 64 });
	upAnim.PushBack({ 384, 192,  32, 64 });
	upAnim.PushBack({ 448, 128,  32, 64 });
	upAnim.PushBack({ 384, 192,  32, 64 });
	upAnim.PushBack({ 416, 192,  32, 64 });
	upAnim.PushBack({ 448, 192,  32, 64 });
	upAnim.PushBack({ 416, 192, 32, 64 });


	upAnim.speed = 0.15;
	upAnim.pingpong = false;


	path.PushBack({ 0, 1.0f }, 150, &downAnim);
	path.PushBack({ 0, -1.0f }, 150, &upAnim);


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
	/*if (attackTimer >= 44)
	{
		App->particles->AddParticle(App->particles->enemyBullet, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		attackTimer = 0;
	}

	attackTimer++;*/
}

void Enemy_GreenSoldier2::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::EXPLOSION || collider->type == Collider::Type::RALIGUN_SHOOT)
	{
		App->player->score += 100;
		App->particles->AddParticle(App->particles->GreenSoilderDeath, position.x, position.y, Collider::Type::NONE);
		App->audio->PlayFx(enemyDeadFx);
	}


}
