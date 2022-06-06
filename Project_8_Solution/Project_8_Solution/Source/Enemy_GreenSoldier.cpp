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
#include "ModuleAudio.h"

Enemy_GreenSoldier::Enemy_GreenSoldier(int x, int y) : Enemy(x, y)
{

	GreenSloideridleAnim.PushBack({ 448, 0, 32, 64 });
	GreenSloideridleAnim.PushBack({ 448, 0, 32, 64 });
	GreenSloideridleAnim.PushBack({ 416, 0, 32, 64 });
	GreenSloideridleAnim.PushBack({ 448, 0, 32, 64 });
	GreenSloideridleAnim.PushBack({ 416, 0, 32, 64 });
	GreenSloideridleAnim.PushBack({ 448, 0, 32, 64 });
	GreenSloideridleAnim.PushBack({ 448, 0, 32, 64 });
	GreenSloideridleAnim.loop = true;
	GreenSloideridleAnim.speed = 0.15f;
	GreenSloideridleAnim.pingpong = false;

	GreenSloiderrightAnim.PushBack({ 225, 384, 32, 64});
	GreenSloiderrightAnim.PushBack({ 225, 384, 32, 64});
	GreenSloiderrightAnim.PushBack({ 225, 448, 32, 64});
	GreenSloiderrightAnim.PushBack({ 225, 384, 32, 64 });
	GreenSloiderrightAnim.PushBack({ 225, 448, 32, 64 });
	GreenSloiderrightAnim.PushBack({ 225, 384, 32, 64 });
	GreenSloiderrightAnim.PushBack({ 225, 384, 32, 64 });
	GreenSloiderrightAnim.loop = true;
	GreenSloiderrightAnim.speed = 0.15f;
	GreenSloiderrightAnim.pingpong = false;
	
	GreenSloiderleftAnim.PushBack({ 285, 384, 32, 64});
	GreenSloiderleftAnim.PushBack({ 285, 384, 32, 64});
	GreenSloiderleftAnim.PushBack({ 285, 448, 32, 64});
	GreenSloiderleftAnim.PushBack({ 285, 384, 32, 64 });
	GreenSloiderleftAnim.PushBack({ 285, 448, 32, 64 });
	GreenSloiderleftAnim.PushBack({ 285, 384, 32, 64 });
	GreenSloiderleftAnim.PushBack({ 285, 384, 32, 64 });
	GreenSloiderleftAnim.loop = true;
	GreenSloiderleftAnim.speed = 0.15f;
	GreenSloiderleftAnim.pingpong = false;

	GreenSloiderbackAnim.PushBack({ 133, 384, 32, 64 });
	GreenSloiderbackAnim.PushBack({ 133, 384, 32, 64 });
	GreenSloiderbackAnim.PushBack({ 133, 446, 32, 64 });
	GreenSloiderbackAnim.PushBack({ 133, 384, 32, 64 });
	GreenSloiderbackAnim.PushBack({ 133, 446, 32, 64 });
	GreenSloiderbackAnim.PushBack({ 133, 384, 32, 64 });
	GreenSloiderbackAnim.PushBack({ 133, 384, 32, 64 });
	GreenSloiderbackAnim.loop = true;
	GreenSloiderbackAnim.speed = 0.15f;
	GreenSloiderbackAnim.pingpong = false;

	//GreenSloiderbackAnim.PushBack();

	attackTimer = 33;

	//collider = App->collisions->AddCollider({100, 0, 30, 55}, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 150);

	collider = App->collisions->AddCollider({100, 0, 30, 60}, Collider::Type::ENEMY, (Module*)App->enemies);
	currentAnim = &GreenSloideridleAnim;
}

void Enemy_GreenSoldier::Update()
{
	if (+App->player->position.y - this->position.y < 300)
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();
		

		Shoot();
	}
	Enemy::Update();
}

void Enemy_GreenSoldier::Draw()
{
	Enemy::Draw();

	float angleDegrees = AngleToPlayerDegrees();

	SDL_Point finalPos{ position.x + (cos(angleDegrees * DEGTORAD) * 100) + 16, position.y + (sin(angleDegrees * DEGTORAD) * 100 ) + 32};
	if (App->collisions->debug)
	{
		App->render->DrawLine(position.x + 16, position.y + 32, finalPos.x, finalPos.y, 255, 255, 255, 255);
	}
}

void Enemy_GreenSoldier::Shoot()
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
			currentAnim = &GreenSloiderrightAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBulletDR, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
		if (angleDegrees >= 61 && angleDegrees <= 130)
		{
			currentAnim = &GreenSloideridleAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBullet, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
		if (angleDegrees >= 131 && angleDegrees <=179 )
		{
			currentAnim = &GreenSloiderleftAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBulletDL, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
		if (angleDegrees <= 0 && angleDegrees >= -179)
		{
			currentAnim = &GreenSloiderbackAnim;
			App->audio->PlayFx(App->player->shotFx);
			App->particles->AddParticle(App->particles->enemyBulletU, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		}
	}
	attackTimer = 0;
}

void Enemy_GreenSoldier::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::EXPLOSION || collider->type == Collider::Type::RALIGUN_SHOOT)
	{
		currentAnim = &death;
		App->player->score += 100;
		App->particles->AddParticle(App->particles->GreenSoilderDeath, position.x, position.y, Collider::Type::NONE);
		App->audio->PlayFx(enemyDeadFx);
	}


}
