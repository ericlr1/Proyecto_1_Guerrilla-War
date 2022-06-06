#include "Enemy_Grenades.h"

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

Enemy_Grenades::Enemy_Grenades(int x, int y) : Enemy(x, y)
{


	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 448, 0, 32, 64 });
	idleAnim.PushBack({ 0, 510, 32, 64 });
	idleAnim.PushBack({ 32, 510, 32, 64 });
	idleAnim.PushBack({ 64, 510, 32, 64 });

	idleAnim.loop = true;
	idleAnim.speed = 0.088f;
	idleAnim.pingpong = false;


	attackTimer = 30;

	//collider = App->collisions->AddCollider({100, 0, 30, 55}, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 150);

	collider = App->collisions->AddCollider({ 100, 0, 30, 60 }, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &idleAnim;
}

void Enemy_Grenades::Update()
{
	if (+App->player->position.y - this->position.y < 300)
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();

		Shoot();
	}
	Enemy::Update();
}

void Enemy_Grenades::Draw()
{
	Enemy::Draw();

	float angleDegrees = AngleToPlayerDegrees();

	SDL_Point finalPos{ position.x + (cos(angleDegrees * DEGTORAD) * 100) + 16, position.y + (sin(angleDegrees * DEGTORAD) * 100) + 32 };
	if (App->collisions->debug)
	{
		App->render->DrawLine(position.x + 16, position.y + 32, finalPos.x, finalPos.y, 255, 255, 255, 255);
	}
}

void Enemy_Grenades::Shoot()
{
	float angleDegrees = AngleToPlayerDegrees();

	LOG("%f", angleDegrees);

	if (attackTimer < 175)
	{
		attackTimer++;
		return;
	}

	if (+App->player->position.y - this->position.y < 300)
	{
		if (angleDegrees >= 1 && angleDegrees <= 60)
		{
			currentAnim = &idleAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->enemygrenade.speed.x = 1;
			App->particles->enemygrenade.speed.y = 1;

			App->particles->AddParticle(App->particles->enemygrenade, position.x + 10, position.y + 35, Collider::Type::NONE);
		}
		if (angleDegrees >= 61 && angleDegrees <= 130)
		{
			currentAnim = &idleAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->enemygrenade.speed.x = 0;
			App->particles->enemygrenade.speed.y = 1;
			App->particles->AddParticle(App->particles->enemygrenade, position.x + 10, position.y + 35, Collider::Type::NONE);
		}		
		if (angleDegrees >=131 && angleDegrees <= 179)
		{
			currentAnim = &idleAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->enemygrenade.speed.x = -1;
			App->particles->enemygrenade.speed.y = 1;
			App->particles->AddParticle(App->particles->enemygrenade, position.x + 10, position.y + 35, Collider::Type::NONE);
		}
	}
	attackTimer = 0;
}

void Enemy_Grenades::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::EXPLOSION || collider->type == Collider::Type::RALIGUN_SHOOT)
	{
		currentAnim = &death;
		App->player->score += 100;
		App->particles->AddParticle(App->particles->GreenSoilderDeath, position.x, position.y, Collider::Type::NONE);
	}


}
