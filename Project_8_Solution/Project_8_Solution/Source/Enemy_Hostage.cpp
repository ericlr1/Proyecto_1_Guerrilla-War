#include "Enemy_Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Enemy.h"
#include "ModulePlayer.h"

Enemy_Hostage::Enemy_Hostage(int x, int y) : Enemy(x, y)
{
	idleAnim.PushBack({ 416, 352, 32, 64 });
	idleAnim.PushBack({ 416, 352, 32, 64 });
	idleAnim.PushBack({ 416, 352, 32, 64 });
	idleAnim.PushBack({ 448, 352, 32, 64 });
	idleAnim.PushBack({ 480, 352, 32, 64 });
	idleAnim.PushBack({ 512, 352, 32, 64 });
	idleAnim.PushBack({ 480, 352, 32, 64 });
	idleAnim.PushBack({ 512, 352, 32, 64 });
	idleAnim.PushBack({ 448, 352, 32, 64 });

	deadAnim.PushBack({ 416, 480, 32, 64 });
	deadAnim.PushBack({ 448, 480, 32, 64 });
	deadAnim.PushBack({ 480, 480, 32, 64 });
	deadAnim.PushBack({ 512, 480, 32, 64 });
	deadAnim.PushBack({ 384, 480, 32, 64 });

	saveAnim.PushBack({ 416, 416, 32, 64 });
	saveAnim.PushBack({ 448, 416, 32, 64 });
	saveAnim.PushBack({ 480, 416, 32, 64 });
	saveAnim.PushBack({ 384, 416, 32, 64 });


	idleAnim.loop = true, deadAnim.loop = false, saveAnim.loop = false;
	idleAnim.speed = 0.04f, deadAnim.speed = 0.04f, saveAnim.speed = 0.04f;
	idleAnim.pingpong = false, deadAnim.pingpong = false, saveAnim.pingpong = false;

	currentAnim = &idleAnim;

	collider = App->collisions->AddCollider({ 100, 0, 30, 55 }, Collider::Type::HOSTAGE, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f }, 160, &idleAnim);

	/*if ("Un enemigo dispara al rehe")
	{
		path.PushBack({ 0.0f, 0.0f }, 160, &deadAnim);

	}
	else if ("Player toca al rehen")
	{
		path.PushBack({ 0.0f, 0.0f }, 160, &saveAnim);

	}
	*/

}

void Enemy_Hostage::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Hostage::Shoot()
{

}



void Enemy_Hostage::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		App->player->score -= 500;
	}
	
	if (collider->type == Collider::Type::BODY)
	{
		App->player->score += 1000;
		App->player->totalGrenades = 50;
	}
	
}
