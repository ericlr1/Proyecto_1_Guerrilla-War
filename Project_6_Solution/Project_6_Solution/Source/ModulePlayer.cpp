#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	// idle 
	idleAnim.PushBack({ 64, 0, 32, 32 });
	idlefootAnim.PushBack({ 224, 0, 32, 32 });

	// move up
	//Body
	upAnim.PushBack({ 64, 0, 32, 32 });
	upAnim.PushBack({ 96, 0, 32, 32 });
	upAnim.PushBack({ 128, 0, 32, 32 });
	upAnim.PushBack({ 96, 0, 32, 32 });
	upAnim.PushBack({ 64, 0, 32, 32 });
	upAnim.PushBack({ 32, 0, 32, 32 });
	upAnim.PushBack({ 0, 0, 32, 32 });
	upAnim.PushBack({ 32, 0, 32, 32 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;
	//Foot arriba
	upfoot1Anim.PushBack({ 224, 0, 32, 32 });
	upfoot1Anim.PushBack({ 192, 0, 32, 32 });
	upfoot1Anim.PushBack({ 160, 0, 32, 32 });
	upfoot1Anim.PushBack({ 192, 0, 32, 32 });
	upfoot1Anim.loop = true;
	upfoot1Anim.speed = 2.0f;
	//Foot abajo
	upfoot2Anim.PushBack({ 224, 0, 32, 32 });
	upfoot2Anim.PushBack({ 160, 0, 32, 32 });
	upfoot2Anim.PushBack({ 160, 0, 32, 32 });
	upfoot2Anim.loop = true;
	upfoot2Anim.speed = 2.0f;

	// move down
	//Body
	downAnim.PushBack({ 64, 128, 32, 32 });
	downAnim.PushBack({ 96, 128, 32, 32 });
	downAnim.PushBack({ 128, 128, 32, 32 });
	downAnim.PushBack({ 96, 128, 32, 32 });
	downAnim.PushBack({ 64, 128, 32, 32 });
	downAnim.PushBack({ 32, 128, 32, 32 });
	downAnim.PushBack({ 0, 128, 32, 32 });
	downAnim.PushBack({ 32, 128, 32, 32 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;
	//Foot
	downfootAnim.PushBack({ 192, 0, 32, 32 });
	downfootAnim.PushBack({ 160, 0, 32, 32 });
	downfootAnim.loop = true;
	downfootAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Characters_Clean.png"); // arcade version
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 150;
	position.y = 120;

	// TODO 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.x += 1;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->particles->AddParticle(App->particles->laserD, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->particles->AddParticle(App->particles->laserU, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->particles->AddParticle(App->particles->laserL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->particles->AddParticle(App->particles->laserUL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->particles->AddParticle(App->particles->laserDL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->particles->AddParticle(App->particles->laserUR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->particles->AddParticle(App->particles->laserDR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);

		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_1] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserDL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_2] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserD, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_3] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserDR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_4] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_6] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_7] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserUL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_8] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserU, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_9] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserUR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}



	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

	// TODO 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Detect collision with a wall. If so, go back to intro screen.
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
}