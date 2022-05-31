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

	if (angleDegrees >= 70 && angleDegrees <= 110)
	{
		App->particles->AddParticle(App->particles->enemyBullet, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
	}
	if (angleDegrees >= 110 && angleDegrees <= 150)
	{
		App->particles->AddParticle(App->particles->enemyBulletDL, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
	}
	attackTimer = 0;
}

void Enemy_GreenSoldier::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		currentAnim = &death;
		App->player->score += 100;
		App->particles->AddParticle(App->particles->GreenSoilderDeath, position.x, position.y, Collider::Type::NONE);
	}


}
