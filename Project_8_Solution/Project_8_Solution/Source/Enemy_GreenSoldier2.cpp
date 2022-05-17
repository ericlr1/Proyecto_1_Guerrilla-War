#include "Enemy_GreenSoldier2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "Enemy.h"

#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_GreenSoldier2::Enemy_GreenSoldier2(int x, int y) : Enemy(x, y)
{
	topAnim.PushBack({ 0,0,32,32 });
	currentAnim = &topAnim;

	botAnim.PushBack({ 160,128,32,32 });
	currentAnim = &botAnim;

#pragma region Animations

	topUp.PushBack({ 0,128,32,32 });
	topUpRight.PushBack({ 0,96,32,32 });
	topRight.PushBack({ 0,64,32,32 });
	topDownRight.PushBack({ 0,32,32,32 });
	topDown.PushBack({ 0,0,32,32 });
	topDownLeft.PushBack({ 0,224,32,32 });
	topLeft.PushBack({ 0,192,32,32 });
	topUpLeft.PushBack({ 0,160,32,32 });
	currentAnim = &topDown;

	botUp.PushBack({ 160,0,32,32 });
	botUpRight.PushBack({ 160,32,32,32 });
	botRight.PushBack({ 160,64,32,32 });
	botDownRight.PushBack({ 160,96,32,32 });
	botDown.PushBack({ 160,0,32,32 });
	botDownLeft.PushBack({ 160,160,32,32 });
	botLeft.PushBack({ 160,192,32,32 });
	botUpLeft.PushBack({ 160,224,32,32 });
	currentAnim = &botDown;

#pragma endregion

	path.PushBack({ 0, -1.0f }, 50);
	path.PushBack({ 0, 1.0f }, 50);


	collider = App->collisions->AddCollider({ 0, 0, 36, 72 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenSoldier2::Update()
{
#pragma region Update Direction

	// Down
	if (degrees > 247.5 && degrees < 292.5)
		looking = Directions::UP;

	// Down right
	else if (degrees > 292.5 && degrees < 337.5)
		looking = Directions::UP_RIGHT;

	// Down left
	else if (degrees > 202.5 && degrees < 247.5)
		looking = Directions::UP_LEFT;

	// Right
	else if (degrees > 337.5 || degrees < 22.5)
		looking = Directions::RIGHT;

	// Left
	else if (degrees > 157.5 && degrees < 202.5)
		looking = Directions::LEFT;

	// Up right
	else if (degrees > 22.5 && degrees < 67.5)
		looking = Directions::DOWN_RIGHT;

	// Up left
	else if (degrees > 112.5 && degrees < 157.5)
		looking = Directions::DOWN_LEFT;

	// Up
	else if (degrees > 67.5 && degrees < 112.5)
		looking = Directions::DOWN;

#pragma endregion


#pragma region Update Animation

	switch (looking)
	{
	case Directions::UP:
		currentAnim = &topUp;
		break;

	case Directions::UP_RIGHT:
		currentAnim = &topUpRight;
		break;

	case Directions::UP_LEFT:
		currentAnim = &topUpLeft;
		break;

	case Directions::RIGHT:
		currentAnim = &topRight;
		break;

	case Directions::LEFT:
		currentAnim = &topLeft;
		break;

	case Directions::DOWN_RIGHT:
		currentAnim = &topDownRight;
		break;
	case Directions::DOWN_LEFT:
		currentAnim = &topDownLeft;
		break;
	case Directions::DOWN:
		currentAnim = &topDown;
		break;
	}

#pragma endregion

	Enemy::Update();
}

void Enemy_GreenSoldier2::Shoot()
{
	if (shootdelay >= 20)
	{
		//App->particles->AddParticle(App->particles->shot_down, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
		//App->particles->AddParticle(App->particles->shot_down_right, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);

		switch (looking)
		{
		case Directions::UP:
			App->particles->AddParticle(App->particles->bulletU, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;

		case Directions::UP_RIGHT:
			App->particles->AddParticle(App->particles->bulletUR, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;

		case Directions::UP_LEFT:
			App->particles->AddParticle(App->particles->bulletUL, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;
			// bug
		case Directions::RIGHT:
			App->particles->AddParticle(App->particles->bullet, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;

		case Directions::LEFT:
			App->particles->AddParticle(App->particles->bulletL, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;

		case Directions::DOWN_RIGHT:
			App->particles->AddParticle(App->particles->bulletDR, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;
		case Directions::DOWN_LEFT:
			App->particles->AddParticle(App->particles->bulletDL, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;
		case Directions::DOWN:
			App->particles->AddParticle(App->particles->bulletD, position.x + 16, position.y + 32, Collider::Type::ENEMY_SHOT);
			break;
		default:
			break;
		}

		shootdelay = 0;
	}

	shootdelay++;
}

void Enemy_GreenSoldier2::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		App->player->score += 500;
	}


}
