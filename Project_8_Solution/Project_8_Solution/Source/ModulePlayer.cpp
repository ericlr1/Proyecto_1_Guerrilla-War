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
	// -IDLE-		[x]
	//_Body
	idleupAnim.PushBack({ 64, 0, 32, 32 });
	idlerightupAnim.PushBack({ 64, 32, 32, 32 });
	idlerightAnim.PushBack({ 64, 64, 32, 32 });
	idlerightdownAnim.PushBack({ 64, 96, 32, 32 });
	idledownAnim.PushBack({ 64, 128, 32, 32 });
	idleleftdownAnim.PushBack({ 64, 160, 32, 32 });
	idleleftAnim.PushBack({ 64, 192, 32, 32 });
	idleleftupAnim.PushBack({ 64, 224, 32, 32 });
	//_Foot
	idleupfootAnim.PushBack({ 224, 0, 32, 32 });
	idlerightupfootAnim.PushBack({ 224, 32, 32, 32 });
	idlerightfootAnim.PushBack({ 224, 64, 32, 32 });
	idlerightdownfootAnim.PushBack({ 224, 96, 32, 32 });
	idledownfootAnim.PushBack({ 224, 128, 32, 32 });
	idleleftdownfootAnim.PushBack({ 224, 160, 32, 32 });
	idleleftfootAnim.PushBack({ 224, 192, 32, 32 });
	idleleftupfootAnim.PushBack({ 224, 224, 32, 32 });

	// -UP-			[x]
	//_Body
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
	//_Foot
	upfootAnim.PushBack({ 224, 0, 32, 32 });
	upfootAnim.PushBack({ 256, 0, 32, 32 });
	upfootAnim.PushBack({ 288, 0, 32, 32 });
	upfootAnim.PushBack({ 192, 0, 32, 32 });
	upfootAnim.PushBack({ 160, 0, 32, 32 });
	upfootAnim.loop = true;
	upfootAnim.speed = 0.1f;
	
	// -DOWN-		[x]
	//_Body
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
	//_Foot
	downfootAnim.PushBack({ 224, 128, 32, 32 });
	downfootAnim.PushBack({ 256, 128, 32, 32 });
	downfootAnim.PushBack({ 288, 128, 32, 32 });
	downfootAnim.PushBack({ 192, 128, 32, 32 });
	downfootAnim.PushBack({ 160, 128, 32, 32 });
	downfootAnim.loop = true;
	downfootAnim.speed = 0.1f;
	
	// -LEFT-		[x]
	//_Body
	leftAnim.PushBack({ 64, 192, 32, 32 });
	leftAnim.PushBack({ 96, 192, 32, 32 });
	leftAnim.PushBack({ 128, 192, 32, 32 });
	leftAnim.PushBack({ 96, 192, 32, 32 });
	leftAnim.PushBack({ 64, 192, 32, 32 });
	leftAnim.PushBack({ 32, 192, 32, 32 });
	leftAnim.PushBack({ 0, 192, 32, 32 });
	leftAnim.PushBack({ 32, 192, 32, 32 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;
	//_Foot
	leftfootAnim.PushBack({ 224, 192, 32, 32 });
	leftfootAnim.PushBack({ 256, 192, 32, 32 });
	leftfootAnim.PushBack({ 288, 192, 32, 32 });
	leftfootAnim.PushBack({ 192, 192, 32, 32 });
	leftfootAnim.PushBack({ 160, 192, 32, 32 });
	leftfootAnim.loop = true;
	leftfootAnim.speed = 0.1f;
	
	// -RIGHT-		[x]
	//_Body
	rightAnim.PushBack({ 64, 64, 32, 32 });
	rightAnim.PushBack({ 96, 64, 32, 32 });
	rightAnim.PushBack({ 128, 64, 32, 32 });
	rightAnim.PushBack({ 96, 64, 32, 32 });
	rightAnim.PushBack({ 64, 64, 32, 32 });
	rightAnim.PushBack({ 32, 64, 32, 32 });
	rightAnim.PushBack({ 0, 64, 32, 32 });
	rightAnim.PushBack({ 32, 64, 32, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
	//_Foot
	rightfootAnim.PushBack({ 224, 64, 32, 32 });
	rightfootAnim.PushBack({ 256, 64, 32, 32 });
	rightfootAnim.PushBack({ 288, 64, 32, 32 });
	rightfootAnim.PushBack({ 192, 64, 32, 32 });
	rightfootAnim.PushBack({ 160, 64, 32, 32 });
	rightfootAnim.loop = true;
	rightfootAnim.speed = 0.1f;

	// -RIGHT/UP-	[x]
	//_Body
	rightAnim.PushBack({ 64, 32, 32, 32 });
	rightAnim.PushBack({ 96, 32, 32, 32 });
	rightAnim.PushBack({ 128, 32, 32, 32 });
	rightAnim.PushBack({ 96, 32, 32, 32 });
	rightAnim.PushBack({ 64, 32, 32, 32 });
	rightAnim.PushBack({ 32, 32, 32, 32 });
	rightAnim.PushBack({ 0, 32, 32, 32 });
	rightAnim.PushBack({ 32, 32, 32, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
	//_Foot
	rightfootAnim.PushBack({ 224, 32, 32, 32 });
	rightfootAnim.PushBack({ 256, 32, 32, 32 });
	rightfootAnim.PushBack({ 288, 32, 32, 32 });
	rightfootAnim.PushBack({ 192, 32, 32, 32 });
	rightfootAnim.PushBack({ 160, 32, 32, 32 });
	rightfootAnim.loop = true;
	rightfootAnim.speed = 0.1f;

	// -RIGHT/DOWN-	[x]
	//_Body
	rightAnim.PushBack({ 64, 96, 32, 32 });
	rightAnim.PushBack({ 96, 96, 32, 32 });
	rightAnim.PushBack({ 128, 96, 32, 32 });
	rightAnim.PushBack({ 96, 96, 32, 32 });
	rightAnim.PushBack({ 64, 96, 32, 32 });
	rightAnim.PushBack({ 32, 96, 32, 32 });
	rightAnim.PushBack({ 0, 96, 32, 32 });
	rightAnim.PushBack({ 32, 96, 32, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
	//_Foot
	rightfootAnim.PushBack({ 224, 96, 32, 32 });
	rightfootAnim.PushBack({ 256, 96, 32, 32 });
	rightfootAnim.PushBack({ 288, 96, 32, 32 });
	rightfootAnim.PushBack({ 192, 96, 32, 32 });
	rightfootAnim.PushBack({ 160, 96, 32, 32 });
	rightfootAnim.loop = true;
	rightfootAnim.speed = 0.1f;

	// -LEFT/UP-	[x]
	//_Body
	rightAnim.PushBack({ 64, 224, 32, 32 });
	rightAnim.PushBack({ 96, 224, 32, 32 });
	rightAnim.PushBack({ 128, 224, 32, 32 });
	rightAnim.PushBack({ 96, 224, 32, 32 });
	rightAnim.PushBack({ 64, 224, 32, 32 });
	rightAnim.PushBack({ 32, 224, 32, 32 });
	rightAnim.PushBack({ 0, 224, 32, 32 });
	rightAnim.PushBack({ 32, 224, 32, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
	//_Foot
	rightfootAnim.PushBack({ 224, 224, 32, 32 });
	rightfootAnim.PushBack({ 256, 224, 32, 32 });
	rightfootAnim.PushBack({ 288, 224, 32, 32 });
	rightfootAnim.PushBack({ 192, 224, 32, 32 });
	rightfootAnim.PushBack({ 160, 224, 32, 32 });
	rightfootAnim.loop = true;
	rightfootAnim.speed = 0.1f;

	// -LEFT/DOWN-	[x]
	//_Body
	rightAnim.PushBack({ 64, 160, 32, 32 });
	rightAnim.PushBack({ 96, 160, 32, 32 });
	rightAnim.PushBack({ 128, 160, 32, 32 });
	rightAnim.PushBack({ 96, 160, 32, 32 });
	rightAnim.PushBack({ 64, 160, 32, 32 });
	rightAnim.PushBack({ 32, 160, 32, 32 });
	rightAnim.PushBack({ 0, 160, 32, 32 });
	rightAnim.PushBack({ 32, 160, 32, 32 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;
	//_Foot
	rightfootAnim.PushBack({ 224, 160, 32, 32 });
	rightfootAnim.PushBack({ 256, 160, 32, 32 });
	rightfootAnim.PushBack({ 288, 160, 32, 32 });
	rightfootAnim.PushBack({ 192, 160, 32, 32 });
	rightfootAnim.PushBack({ 160, 160, 32, 32 });
	rightfootAnim.loop = true;
	rightfootAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Characters_Clean.png"); // arcade version
	if (facing == 0) // [x]
	{
		currentAnimation = &idleupAnim;
		currentAnimation2 = &idleupfootAnim;
		currentAnimation3 = &idleupfootAnim;
	}
	if (facing == 1) // [x]
	{
		currentAnimation = &idlerightupAnim;
		currentAnimation2 = &idlerightupfootAnim;
		currentAnimation3 = &idlerightupfootAnim;
	}
	if (facing == 2) // [x]
	{
		currentAnimation = &idlerightAnim;
		currentAnimation2 = &idlerightfootAnim;
		currentAnimation3 = &idlerightfootAnim;
	}
	if (facing == 3) // [x]
	{
		currentAnimation = &idlerightdownAnim;
		currentAnimation2 = &idlerightdownfootAnim;
		currentAnimation3 = &idlerightdownfootAnim;
	}
	if (facing == 4) // [x]
	{
		currentAnimation = &idledownAnim;
		currentAnimation2 = &idledownfootAnim;
		currentAnimation3 = &idledownfootAnim;
	}
	if (facing == 5) // [x]
	{
		currentAnimation = &idleleftdownAnim;
		currentAnimation2 = &idleleftdownfootAnim;
		currentAnimation3 = &idleleftdownfootAnim;
	}
	if (facing == 6) // []
	{
		currentAnimation = &idleleftAnim;
		currentAnimation2 = &idleleftfootAnim;
		currentAnimation3 = &idleleftfootAnim;
	}
	if (facing == 7) // []
	{
		currentAnimation = &idleleftupAnim;
		currentAnimation2 = &idleleftupfootAnim;
		currentAnimation3 = &idleleftfootAnim;
	}


	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 200;
	position.y = 3250;

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
		if (facing == 0)
		{
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
		}
		if (facing == 1)
		{
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
		}
		/*if (facing == 2)
		{
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}
		}
		if (facing == 3)
		{
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}
		}
		if (facing == 4)
		{
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}
		}
		if (facing == 5)
		{
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}
		}
		if (facing == 6)
		{
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}
		}
		if (facing == 7)
		{
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}
		}*/
	}
	

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (facing == 0)
		{
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
		}
		if (facing == 1)
		{
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		if (facing == 0)
		{
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
		}
		if (facing == 1)
		{
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (facing == 0)
		{
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
		}
		if (facing == 1)
		{
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
		}
	}

	//Rotaci�n del personaje Q y E
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

	// Comprobaciones de la orientaci�n para realizar los disparos 
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
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
	if (facing == 0)
	{
		currentAnimation = &idleupAnim,
		currentAnimation2 = &idleupfootAnim,
		currentAnimation3 = &idleupfootAnim;
	}
	if (facing == 1)
	{
		currentAnimation = &idlerightupAnim,
		currentAnimation2 = &idlerightupfootAnim,
		currentAnimation3 = &idlerightupfootAnim;
	}
	if (facing == 2)
	{
		currentAnimation = &idlerightAnim,
		currentAnimation2 = &idlerightfootAnim,
		currentAnimation3 = &idlerightfootAnim;
	}
	if (facing == 3)
	{
		currentAnimation = &idlerightdownAnim;
		currentAnimation2 = &idlerightdownfootAnim;
		currentAnimation3 = &idlerightdownfootAnim;
	}
	if (facing == 4)
	{
		currentAnimation = &idledownAnim,
		currentAnimation2 = &idledownfootAnim,
		currentAnimation3 = &idledownfootAnim;
	}
	if (facing == 5)
	{
		currentAnimation = &idleleftdownAnim;
		currentAnimation2 = &idleleftdownfootAnim;
		currentAnimation3 = &idleleftdownfootAnim;
	}
	if (facing == 6)
	{
		currentAnimation = &idleleftAnim,
		currentAnimation2 = &idleleftfootAnim,
		currentAnimation3 = &idleleftfootAnim;
	}
	if (facing == 7)
	{
		currentAnimation = &idleleftupAnim;
		currentAnimation2 = &idleleftupfootAnim;
		currentAnimation3 = &idleleftupfootAnim;
	}
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();
	currentAnimation2->Update();
	currentAnimation3->Update();

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
		SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
		SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();

		App->render->Blit(texture, position.x, position.y + 30, &rect3);
		App->render->Blit(texture, position.x, position.y + 30, &rect2);
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