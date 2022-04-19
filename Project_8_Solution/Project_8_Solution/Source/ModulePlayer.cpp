#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
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

	texture = App->textures->Load("Assets/Sprites/Characters_Clean.png"); // arcade version
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Music/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Music/explosion.wav");

	position.x = 150;
	position.y = 120;

	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.y += 1;
	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)
	{
		facing = 0;

	}



	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	//Rotación del personaje Q y E
	if (App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_DOWN)
	{
		if (facing >= 0 && facing < 7)
		{
			facing = facing + 1;
			exit;
		}
		else
		{
			facing = 0;
		}
	}

	if (App->input->keys[SDL_SCANCODE_Q] == Key_State::KEY_DOWN)
	{
		if (facing > 0 && facing <= 7)
		{
			facing = facing - 1;
			exit;
		}
		else
		{
			facing = 7;
		}
	}

	// Comprobaciones de la orientación para realizar los disparos 
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{

		//La variable facing aumenta al rotar hacia la derecha (Como las agujas del reloj)

		if (facing == 0)
		{
			App->particles->AddParticle(App->particles->laserU, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
		if (facing == 1)
		{
			App->particles->AddParticle(App->particles->laserUR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
		if (facing == 2)
		{
			App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
		if (facing == 3)
		{
			App->particles->AddParticle(App->particles->laserDR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
		if (facing == 4)
		{
			App->particles->AddParticle(App->particles->laserD, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
		if (facing == 5)
		{
			App->particles->AddParticle(App->particles->laserDL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
		if (facing == 6)
		{
			App->particles->AddParticle(App->particles->laserL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
		if (facing == 7)
		{
			App->particles->AddParticle(App->particles->laserUL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(laserFx);
		}
	}

	if (App->input->keys[SDL_SCANCODE_KP_1] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserDL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_2] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserD, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_3] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserDR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_4] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_6] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_7] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserUL, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_KP_8] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserU, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}
	if (App->input->keys[SDL_SCANCODE_KP_9] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laserUR, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
	
}
Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		//TODO 3: Go back to the intro scene when the player gets killed
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}
}