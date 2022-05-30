#include "Enemy_RedSoldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_render.h"
#include "ModuleParticles.h"
#include "Enemy.h"
#include <math.h>
#include <stdio.h>




Enemy_RedSoldier::Enemy_RedSoldier(int x, int y) : Enemy(x, y)
{

	alpha = 0.0f;

	front.PushBack({ 448, 0, 32, 64 });
	front.PushBack({ 448, 0, 32, 64 });
	front.PushBack({ 416, 0, 32, 64 });
	front.PushBack({ 448, 0, 32, 64 });
	front.PushBack({ 416, 0, 32, 64 });
	front.PushBack({ 448, 0, 32, 64 });
	front.PushBack({ 448, 0, 32, 64 });
	front.loop = true;
	front.speed = 0.15f;
	front.pingpong = false;
	currentAnim = &front;
	//collider = App->collisions->AddCollider({100, 0, 30, 55}, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 150, &front);

	collider = App->collisions->AddCollider({ 100, 0, 30, 60 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_RedSoldier::Update()
{
	cx = App->render->camera.x;
	cy = App->render->camera.y;
	rx = App->player->position.x - cx;
	ry = -(App->player->position.y - cy);
	alpha = atan2(ry, rx);

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Shoot();
	Enemy::Update();
}
void Enemy_RedSoldier::Shoot()
{
	if (attackTimer >= 44)
	{
		App->particles->AddParticle(App->particles->enemyBullet, position.x + 10, position.y + 35, Collider::Type::ENEMY_SHOT);
		attackTimer = 0;
	}

	attackTimer++;
}
void Enemy_RedSoldier::Draw()
{
  
}

void Enemy_RedSoldier::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		App->player->score += 100;
	}


}