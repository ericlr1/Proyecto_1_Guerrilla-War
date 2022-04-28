#include "Enemy_GreenSoldier2.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenSoldier2::Enemy_GreenSoldier2(int x, int y) : Enemy(x, y)
{
	runUpAnim.PushBack({ 384, 64, 32, 64 });
	runUpAnim.PushBack({ 384, 0, 32, 64 });
	runUpAnim.PushBack({ 384, 128, 32, 64 });
	runUpAnim.PushBack({ 448, 64, 32, 64 });
	runUpAnim.PushBack({ 416, 64, 32, 64 }); //
	runUpAnim.PushBack({ 448, 64, 32, 64 });
	runUpAnim.PushBack({ 384, 128, 32, 64 });
	runUpAnim.PushBack({ 384, 0, 32, 64 });
	runUpAnim.PushBack({ 384, 64, 32, 64 });

	runDownAnim.PushBack({ 448, 128, 32, 64 });
	runDownAnim.PushBack({ 416, 128, 32, 64 });
	runDownAnim.PushBack({ 448, 192, 32, 64 });
	runDownAnim.PushBack({ 416, 192, 32, 64 });
	runDownAnim.PushBack({ 384, 192, 32, 64 }); //
	runDownAnim.PushBack({ 416, 192, 32, 64 });
	runDownAnim.PushBack({ 448, 192, 32, 64 });
	runDownAnim.PushBack({ 416, 128, 32, 64 });
	runDownAnim.PushBack({ 448, 128, 32, 64 });
	
	runUpAnim.loop = true, runDownAnim.loop = true;
	runUpAnim.speed = 0.15f, runDownAnim.speed = 0.15f;
	runUpAnim.pingpong = false, runDownAnim.pingpong = false;

	currentAnim = &runUpAnim;

	collider = App->collisions->AddCollider({ 100, 0, 30, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 1.0f }, 160, &runUpAnim);
	path.PushBack({ 0.0f, -1.0f }, 160, &runDownAnim);

	collider = App->collisions->AddCollider({ 100, 0, 30, 60 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenSoldier2::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
