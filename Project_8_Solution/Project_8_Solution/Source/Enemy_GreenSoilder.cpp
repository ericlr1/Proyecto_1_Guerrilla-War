#include "Enemy_GreenSoilder.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenSoilder::Enemy_GreenSoilder(int x, int y) : Enemy(x, y)
{
	front.PushBack({5, 108, 31, 29});
	front.PushBack({4, 141, 31, 29});
	front.PushBack({38, 108, 31, 29});
	front.speed = 0.1f;
	//front.pingpong = true;

	back.PushBack({170, 108, 31, 29});
	back.PushBack({170, 141, 31, 29});
	back.PushBack({137, 108, 31, 29});
	back.speed = 0.1f;
	//back.pingpong = true;

	path.PushBack({ 0.0f, 0.0f}, 150, &front);
	
	//De momento est� quieto para que sea mas facil trabajar
	//path.PushBack({ 0.0f, 0.5f}, 150, &front);
	//path.PushBack({ 0.0f, -0.5f}, 150, &back);

	collider = App->collisions->AddCollider({100, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
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
