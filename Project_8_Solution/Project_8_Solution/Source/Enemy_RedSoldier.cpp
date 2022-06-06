#include "Enemy_RedSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <math.h>
#include <stdio.h>
#include "SDL/include/SDL_render.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

Enemy_RedSoldier::Enemy_RedSoldier(int x, int y) : Enemy(x, y)
{

	RedSloideridleAnim.PushBack({ 512, 0, 32, 64 });
	RedSloideridleAnim.PushBack({ 512, 0, 32, 64 });
	RedSloideridleAnim.PushBack({ 512, 0, 32, 64 });
	RedSloideridleAnim.PushBack({ 512, 0, 32, 64 });
	RedSloideridleAnim.PushBack({ 512, 0, 32, 64 });
	RedSloideridleAnim.PushBack({ 480, 0, 32, 64 });
	RedSloideridleAnim.loop = true;
	RedSloideridleAnim.speed = 0.15f;
	RedSloideridleAnim.pingpong = false;


	RedSloiderrightAnim.PushBack({ 298, 632, 32, 64 });
	RedSloiderrightAnim.PushBack({ 298, 632, 32, 64 });
	RedSloiderrightAnim.PushBack({ 298, 632+64, 32, 64 });
	RedSloiderrightAnim.PushBack({ 298, 632, 32, 64 });
	RedSloiderrightAnim.PushBack({ 298, 632+64, 32, 64 });
	RedSloiderrightAnim.PushBack({ 298, 632, 32, 64 });
	RedSloiderrightAnim.PushBack({ 298, 632, 32, 64 });
	RedSloiderrightAnim.loop = true;
	RedSloiderrightAnim.speed = 0.15f;
	RedSloiderrightAnim.pingpong = false;

	RedSloiderleftAnim.PushBack({ 296 + 64, 632, 31, 64 });
	RedSloiderleftAnim.PushBack({ 296 + 64, 632, 31, 64 });
	RedSloiderleftAnim.PushBack({ 296 + 64, 632 + 64, 31, 64 });
	RedSloiderleftAnim.PushBack({ 296 + 64, 632, 31, 64 });
	RedSloiderleftAnim.PushBack({ 296 + 64, 632 + 64, 31, 64 });
	RedSloiderleftAnim.PushBack({ 296 + 64, 632, 31, 64 });
	RedSloiderleftAnim.PushBack({ 296 + 64, 632, 31, 64 });
	RedSloiderleftAnim.loop = true;
	RedSloiderleftAnim.speed = 0.15f;
	RedSloiderleftAnim.pingpong = false;

	RedSloiderbackAnim.PushBack({ 204, 632, 32, 64 });
	RedSloiderbackAnim.PushBack({ 204, 632, 32, 64 });
	RedSloiderbackAnim.PushBack({ 204, 632+64, 32, 64 });
	RedSloiderbackAnim.PushBack({ 204, 632, 32, 64 });
	RedSloiderbackAnim.PushBack({ 204, 632+64, 32, 64 });
	RedSloiderbackAnim.PushBack({ 204, 632, 32, 64 });
	RedSloiderbackAnim.PushBack({ 204, 632, 32, 64 });
	RedSloiderbackAnim.loop = true;
	RedSloiderbackAnim.speed = 0.15f;
	RedSloiderbackAnim.pingpong = false;


	//collider = App->collisions->AddCollider({100, 0, 30, 55}, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 150);

	collider = App->collisions->AddCollider({ 100, 0, 30, 60 }, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &RedSloideridleAnim;
}

void Enemy_RedSoldier::Update()
{
	if (+App->player->position.y - this->position.y < 300)
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();
		
		Shoot();
	}
	Enemy::Update();
}

void Enemy_RedSoldier::Draw()
{
	Enemy::Draw();

	float angleDegrees = AngleToPlayerDegrees();

	SDL_Point finalPos{ position.x + (cos(angleDegrees * DEGTORAD) * 100) + 16, position.y + (sin(angleDegrees * DEGTORAD) * 100) + 32 };
	if (App->collisions->debug)
	{
		App->render->DrawLine(position.x + 16, position.y + 32, finalPos.x, finalPos.y, 255, 255, 255, 255);
	}
}

void Enemy_RedSoldier::Shoot()
{
	float angleDegrees = AngleToPlayerDegrees();

	LOG("%f", angleDegrees);

	if (attackTimer < 44)
	{
		attackTimer++;
		return;
	}

	if (+App->player->position.y - this->position.y < 300)
	{

		if (angleDegrees >= 1 && angleDegrees <= 60)
		{
			currentAnim = &RedSloiderrightAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBulletDR, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
		if (angleDegrees >= 61 && angleDegrees <= 130)

		{
			currentAnim = &RedSloideridleAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBullet, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
		if (angleDegrees >= 131 && angleDegrees <= 179)
		{
			currentAnim = &RedSloiderleftAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBulletDL, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
		if (angleDegrees <= 0 && angleDegrees >= -179)
		{
			currentAnim = &RedSloiderbackAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBulletU, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
	}
	attackTimer = 0;
}

void Enemy_RedSoldier::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::EXPLOSION || collider->type == Collider::Type::RALIGUN_SHOOT)
	{
		currentAnim = &death;
		App->player->score += 100;
		App->particles->AddParticle(App->particles->RedSoilderDeath, position.x, position.y, Collider::Type::NONE);
		App->audio->PlayFx(enemyDeadFx);
	}


}
