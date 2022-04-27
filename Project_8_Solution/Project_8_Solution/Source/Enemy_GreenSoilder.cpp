#include "Enemy_GreenSoilder.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenSoilder::Enemy_GreenSoilder(int x, int y) : Enemy(x, y)
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

	path.PushBack({ 0.0f, 0.0f}, 150, &idleAnim);

	collider = App->collisions->AddCollider({100, 0, 30, 55}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenSoilder::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
