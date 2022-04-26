#include "Enemy_GreenSoilder.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenSoilder::Enemy_GreenSoilder(int x, int y) : Enemy(x, y)
{
	
	//_Body
	leftdownAnim.PushBack({ 64, 194, 32, 32 });
	leftdownAnim.PushBack({ 96, 194, 32, 32 });
	leftdownAnim.PushBack({ 64, 194, 32, 32 });
	leftdownAnim.PushBack({ 32, 194, 32, 32 });
	leftdownAnim.PushBack({ 0, 194, 32, 32 });
	leftdownAnim.PushBack({ 32, 194, 32, 32 });
	leftdownAnim.speed = 0.1f;
	//_Foot
	leftdownfootAnim.PushBack({ 165, 194, 32, 32 });
	leftdownfootAnim.PushBack({ 198, 194, 32, 32 });
	leftdownfootAnim.PushBack({ 228, 194, 32, 32 });
	leftdownfootAnim.PushBack({ 132, 194, 32, 32 });
	leftdownfootAnim.PushBack({ 98, 194, 32, 32 });
	leftdownfootAnim.speed = 0.1f;
	//back.pingpong = true;
	
	collider = App->collisions->AddCollider({100, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.0f, 0.0f}, 150, &leftdownAnim);
	path.PushBack({ 0.0f, 0.0f }, 100, &leftdownfootAnim);
	//De momento está quieto para que sea mas facil trabajar
	//path.PushBack({ 0.0f, 0.5f}, 150, &front);
	//path.PushBack({ 0.0f, -0.5f}, 150, &back);


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
