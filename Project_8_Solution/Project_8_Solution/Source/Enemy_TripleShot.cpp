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
#include "ModuleAudio.h"

Enemy_TripleShot::Enemy_TripleShot(int x, int y) : Enemy(x, y)
{

	idleAnim.PushBack({ 334, 555, 27, 47 });
	idleAnim.PushBack({ 334, 555, 27, 47 });
	idleAnim.PushBack({ 303, 555, 26, 47 });
	idleAnim.PushBack({ 334, 555, 27, 47 });
	idleAnim.PushBack({ 303, 555, 26, 47 });	
	idleAnim.PushBack({ 334, 555, 27, 47 });
	idleAnim.PushBack({ 334, 555, 27, 47 });

	

	idleAnim.loop = true;
	idleAnim.speed = 0.15f;
	idleAnim.pingpong = false;

	currentAnim = &idleAnim;

	attackTimer = 33;

	collider = App->collisions->AddCollider({ 100, 0, 30, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 160, &idleAnim);
}

void Enemy_TripleShot::Update()
{
	if (+App->player->position.y - this->position.y < 300)
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();
		currentAnim = path.GetCurrentAnimation();

		Shoot();
	}
	Enemy::Update();
}



void Enemy_TripleShot::Shoot()
{
	if (+App->player->position.y - this->position.y < 300)
	{

		if (attackTimer >= 44)
		{
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBullet, position.x + 13, position.y + 32, Collider::Type::ENEMY_SHOT);
			App->particles->AddParticle(App->particles->enemyBulletDLcustom, position.x + 13, position.y + 32, Collider::Type::ENEMY_SHOT);
			App->particles->AddParticle(App->particles->enemyBulletDRcustom, position.x + 13, position.y + 32, Collider::Type::ENEMY_SHOT);
			attackTimer = 0;
		}
	}

	attackTimer++;
}

void Enemy_TripleShot::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::EXPLOSION || collider->type == Collider::Type::RALIGUN_SHOOT)
	{
		App->player->score += 100;
		App->particles->AddParticle(App->particles->GreenSoilderDeath, position.x, position.y, Collider::Type::NONE);
		App->audio->PlayFx(enemyDeadFx);
	}


}
