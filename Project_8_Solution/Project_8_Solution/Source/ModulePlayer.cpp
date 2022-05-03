#include "ModulePlayer.h"

#include "Application.h"
#include "Animation.h"

#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLose.h"
#include "SceneLogo.h"

#include "SDL/include/SDL_scancode.h"

#include <stdio.h>

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
	rightupAnim.PushBack({ 64, 32, 32, 32 });
	rightupAnim.PushBack({ 96, 32, 32, 32 });
	rightupAnim.PushBack({ 128, 32, 32, 32 });
	rightupAnim.PushBack({ 96, 32, 32, 32 });
	rightupAnim.PushBack({ 64, 32, 32, 32 });
	rightupAnim.PushBack({ 32, 32, 32, 32 });
	rightupAnim.PushBack({ 0, 32, 32, 32 });
	rightupAnim.PushBack({ 32, 32, 32, 32 });
	rightupAnim.loop = true;
	rightupAnim.speed = 0.1f;
	//_Foot
	rightupfootAnim.PushBack({ 224, 32, 32, 32 });
	rightupfootAnim.PushBack({ 256, 32, 32, 32 });
	rightupfootAnim.PushBack({ 288, 32, 32, 32 });
	rightupfootAnim.PushBack({ 192, 32, 32, 32 });
	rightupfootAnim.PushBack({ 160, 32, 32, 32 });
	rightupfootAnim.loop = true;
	rightupfootAnim.speed = 0.1f;

	// -RIGHT/DOWN-	[x]
	//_Body
	rightdownAnim.PushBack({ 64, 96, 32, 32 });
	rightdownAnim.PushBack({ 96, 96, 32, 32 });
	rightdownAnim.PushBack({ 128, 96, 32, 32 });
	rightdownAnim.PushBack({ 96, 96, 32, 32 });
	rightdownAnim.PushBack({ 64, 96, 32, 32 });
	rightdownAnim.PushBack({ 32, 96, 32, 32 });
	rightdownAnim.PushBack({ 0, 96, 32, 32 });
	rightdownAnim.PushBack({ 32, 96, 32, 32 });
	rightdownAnim.loop = true;
	rightdownAnim.speed = 0.1f;
	//_Foot
	rightdownfootAnim.PushBack({ 224, 96, 32, 32 });
	rightdownfootAnim.PushBack({ 256, 96, 32, 32 });
	rightdownfootAnim.PushBack({ 288, 96, 32, 32 });
	rightdownfootAnim.PushBack({ 192, 96, 32, 32 });
	rightdownfootAnim.PushBack({ 160, 96, 32, 32 });
	rightdownfootAnim.loop = true;
	rightdownfootAnim.speed = 0.1f;

	// -LEFT/UP-	[x]
	//_Body
	leftupAnim.PushBack({ 64, 224, 32, 32 });
	leftupAnim.PushBack({ 96, 224, 32, 32 });
	leftupAnim.PushBack({ 128, 224, 32, 32 });
	leftupAnim.PushBack({ 96, 224, 32, 32 });
	leftupAnim.PushBack({ 64, 224, 32, 32 });
	leftupAnim.PushBack({ 32, 224, 32, 32 });
	leftupAnim.PushBack({ 0, 224, 32, 32 });
	leftupAnim.PushBack({ 32, 224, 32, 32 });
	leftupAnim.loop = true;
	leftupAnim.speed = 0.1f;
	//_Foot
	leftupfootAnim.PushBack({ 224, 224, 32, 32 });
	leftupfootAnim.PushBack({ 256, 224, 32, 32 });
	leftupfootAnim.PushBack({ 288, 224, 32, 32 });
	leftupfootAnim.PushBack({ 192, 224, 32, 32 });
	leftupfootAnim.PushBack({ 160, 224, 32, 32 });
	leftupfootAnim.loop = true;
	leftupfootAnim.speed = 0.1f;

	// -LEFT/DOWN-	[x]
	//_Body
	leftdownAnim.PushBack({ 64, 160, 32, 32 });
	leftdownAnim.PushBack({ 96, 160, 32, 32 });
	leftdownAnim.PushBack({ 128, 160, 32, 32 });
	leftdownAnim.PushBack({ 96, 160, 32, 32 });
	leftdownAnim.PushBack({ 64, 160, 32, 32 });
	leftdownAnim.PushBack({ 32, 160, 32, 32 });
	leftdownAnim.PushBack({ 0, 160, 32, 32 });
	leftdownAnim.PushBack({ 32, 160, 32, 32 });
	leftdownAnim.loop = true;
	leftdownAnim.speed = 0.1f;
	//_Foot
	leftdownfootAnim.PushBack({ 224, 160, 32, 32 });
	leftdownfootAnim.PushBack({ 256, 160, 32, 32 });
	leftdownfootAnim.PushBack({ 288, 160, 32, 32 });
	leftdownfootAnim.PushBack({ 192, 160, 32, 32 });
	leftdownfootAnim.PushBack({ 160, 160, 32, 32 });
	leftdownfootAnim.loop = true;
	leftdownfootAnim.speed = 0.1f;

	//Water
	
	water.PushBack({192,256,32,32 });
	water.PushBack({224,256,32,32 });
	water.PushBack({256,256,32,32 });
	
	water.loop = true;
	water.speed = 0.1f;
	water.pingpong = true;

	//trench

	trench.PushBack({ 160,256,32,32 });
	trench.PushBack({ 160,288,32,32 });
	trench.PushBack({ 160,288,32,32 });

	trench.loop = true;
	trench.speed = 0.1f;
	trench.pingpong = false;

	//Weapon animation
	
	// -UP-	[x]
	//Idle
	widleup.PushBack({ 0, 0, 32, 32 });
	widleup.loop = false;
	widleup.speed = 0.2f;
	widleup.pingpong = false;
	//Fire
	wfireup.PushBack({ 0, 32, 32, 32 });
	wfireup.loop = false;
	wfireup.speed = 0.2f;
	wfireup.pingpong = false;

	// -RIGHT/UP-	[x]
	//Idle
	widlerightup.PushBack({ 32, 0, 32, 32 });
	widlerightup.loop = false;
	widlerightup.speed = 0.2f;
	widlerightup.pingpong = false;
	//Fire
	wfirerightup.PushBack({ 32, 32, 32, 32 });
	wfirerightup.loop = false;
	wfirerightup.speed = 0.2f;
	wfirerightup.pingpong = false;
	
	// -RIGHT-	[x]
	//Idle
	widleright.PushBack({ 64, 0, 32, 32 });
	widleright.loop = false;
	widleright.speed = 0.2f;
	widleright.pingpong = false;
	//Fire
	wfireright.PushBack({ 64, 32, 32, 32 });
	wfireright.loop = false;
	wfireright.speed = 0.2f;
	wfireright.pingpong = false;
	
	// -RIGHT/DOWN-	[x]
	//Idle
	widlerightdown.PushBack({ 96, 0, 32, 32 });
	widlerightdown.loop = false;
	widlerightdown.speed = 0.2f;
	widlerightdown.pingpong = false;
	//Fire
	wfirerightdown.PushBack({ 96, 32, 32, 32 });
	wfirerightdown.loop = false;
	wfirerightdown.speed = 0.2f;
	wfirerightdown.pingpong = false;
	
	// -DOWN-	[x]
	//Idle
	widledown.PushBack({ 128, 0, 32, 32 });
	widledown.loop = false;
	widledown.speed = 0.2f;
	widledown.pingpong = false;
	//Fire
	wfiredown.PushBack({ 128, 32, 32, 32 });
	wfiredown.loop = false;
	wfiredown.speed = 0.2f;
	wfiredown.pingpong = false;
	
	// -LEFT/DOWN-	[x]
	//Idle
	widleleftdown.PushBack({ 160, 0, 32, 32 });
	widleleftdown.loop = false;
	widleleftdown.speed = 0.2f;
	widleleftdown.pingpong = false;
	//Fire
	wfireleftdown.PushBack({ 160, 32, 32, 32 });
	wfireleftdown.loop = false;
	wfireleftdown.speed = 0.2f;
	wfireleftdown.pingpong = false;
	
	// -LEFT-	[x]
	//Idle
	widleleft.PushBack({ 192, 0, 32, 32 });
	widleleft.loop = false;
	widleleft.speed = 0.2f;
	widleleft.pingpong = false;
	//Fire
	wfireleft.PushBack({ 192, 32, 32, 32 });
	wfireleft.loop = false;
	wfireleft.speed = 0.2f;
	wfireleft.pingpong = false;
	
	// -LEFT/UP-	[X]
	//Idle
	widleleftup.PushBack({ 224, 0, 32, 32 });
	widleleftup.loop = false;
	widleleftup.speed = 0.2f;
	widleleftup.pingpong = false;
	//Fire
	wfireleftup.PushBack({ 224, 32, 32, 32 });
	wfireleftup.loop = false;
	wfireleftup.speed = 0.2f;
	wfireleftup.pingpong = false;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	weaponTexture = App->textures->Load("Assets/Sprites/weapon.png"); //Weapon
	texture = App->textures->Load("Assets/Sprites/Characters_Clean.png"); // arcade version
	
	//Reset de la score
	score = 0;

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUV"};
	scoreFont = App->fonts->Load("Assets/Sprites/fonts.png", lookupTable, 2);


	//Colider que funciona (Arreglar posicion colliders)
	

	switch (facing)
	{
	case 0:
		currentAnimation = &idleupAnim;
		currentAnimation2 = &idleupfootAnim;
		currentAnimation3 = &widleup;
		break;

	case 1:
		currentAnimation = &idlerightupAnim;
		currentAnimation2 = &idlerightupfootAnim;
		currentAnimation3 = &widlerightup;
		break;

	case 2:
		currentAnimation = &idlerightAnim;
		currentAnimation2 = &idlerightfootAnim;
		currentAnimation3 = &widleright;
		break;

	case 3:
		currentAnimation = &idlerightdownAnim;
		currentAnimation2 = &idlerightdownfootAnim;
		currentAnimation3 = &widlerightdown;
		break;

	case 4:
		currentAnimation = &idledownAnim;
		currentAnimation2 = &idledownfootAnim;
		currentAnimation3 = &widledown;
		break;

	case 5:
		currentAnimation = &idleleftdownAnim;
		currentAnimation2 = &idleleftdownfootAnim;
		currentAnimation3 = &widleleftdown;
		break;

	case 6:
		currentAnimation = &idleleftAnim;
		currentAnimation2 = &idleleftfootAnim;
		currentAnimation3 = &widleleft;
		break;

	case 7:
		currentAnimation = &idleleftupAnim;
		currentAnimation2 = &idleleftupfootAnim;
		currentAnimation3 = &widleleftup;
		break;
	}



	bulletFx = App->audio->LoadFx("Assets/Fx/sounds_gwar-153 (1).wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/sounds_gwar-195 (1).wav");

	//Player position
	position.x = 200;
	position.y = 3250;
	destroyed = false;
	collider = App->collisions->AddCollider({ 0,0, 15,30 }, Collider::Type::BODY, this);
	collider_foot = App->collisions->AddCollider({ 0,0,12,11 }, Collider::Type::FOOT, this);
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
	
	//Auto kill
	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		
		//destroyed = true;
	}

	//Auto win
	if (App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 100);
		destroyed = true;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		
		switch (facing)
		{
		case 0:
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
			break;
		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}
			break;
		}
	}
	

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		
		switch (facing)
		{
		case 0:
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
			break;

		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}
			break;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
	
		switch (facing)
		{
		case 0:
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
			break;

		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}
			break;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;

		switch (facing)
		{
		case 0:
			if (currentAnimation != &upAnim && currentAnimation2 != &upfootAnim)
			{
				upAnim.Reset();
				upfootAnim.Reset();
				currentAnimation = &upAnim;
				currentAnimation2 = &upfootAnim;
			}
			break;

		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}
			break;
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

		switch (facing)
		{
		case 0:
			App->particles->AddParticle(App->particles->bulletU, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfireup;
			break;

		case 1:
			App->particles->AddParticle(App->particles->bulletUR, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfirerightup;
			break;

		case 2:
			App->particles->AddParticle(App->particles->bullet, position.x + 20, position.y + 25, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfireright;
			break;

		case 3:
			App->particles->AddParticle(App->particles->bulletDR, position.x + 12, position.y + 30, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfirerightdown;
			break;

		case 4:
			App->particles->AddParticle(App->particles->bulletD, position.x + 10, position.y + 25, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfiredown;
			break;

		case 5:
			App->particles->AddParticle(App->particles->bulletDL, position.x + 10, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfireleftdown;
			break;

		case 6:
			App->particles->AddParticle(App->particles->bulletL, position.x + 5, position.y + 20, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfireleft;
			break;

		case 7:
			App->particles->AddParticle(App->particles->bulletUL, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
			App->audio->PlayFx(bulletFx);
			currentAnimation3 = &wfireleftup;
			break;
		}
	}


	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
	{
		
		switch (facing)
		{
		case 0:
			currentAnimation = &idleupAnim;
			currentAnimation2 = &idleupfootAnim;
			break;

		case 1:
			currentAnimation = &idlerightupAnim;
			currentAnimation2 = &idlerightupfootAnim;
			break;

		case 2:
			currentAnimation = &idlerightAnim;
			currentAnimation2 = &idlerightfootAnim;
			break;

		case 3:
			currentAnimation = &idlerightdownAnim;
			currentAnimation2 = &idlerightdownfootAnim;
			break;

		case 4:
			currentAnimation = &idledownAnim;
			currentAnimation2 = &idledownfootAnim;
			break;

		case 5:
			currentAnimation = &idleleftdownAnim;
			currentAnimation2 = &idleleftdownfootAnim;
			break;

		case 6:
			currentAnimation = &idleleftAnim;
			currentAnimation2 = &idleleftfootAnim;
			break;

		case 7:
			currentAnimation = &idleleftupAnim;
			currentAnimation2 = &idleleftupfootAnim;
			break;
		}
		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE)
		{
			
			switch (facing)
			{
			case 0:
				currentAnimation3 = &widleup;
				break;

			case 1:
				currentAnimation3 = &widlerightup;
				break;

			case 2:
				currentAnimation3 = &widleright;
				break;

			case 3:
				currentAnimation3 = &widlerightdown;
				break;

			case 4:
				currentAnimation3 = &widledown;
				break;

			case 5:
				currentAnimation3 = &widleleftdown;
				break;

			case 6:
				currentAnimation3 = &widleleft;
				break;

			case 7:
				currentAnimation3 = &widleleftup;
				break;
			}

		}
	}
	
	collider->SetPos(position.x+8, position.y+17);
	collider_foot->SetPos(position.x + 10, position.y + 45);
	
	//Posicion de los colliders conforme se mueve la camara
	currentAnimation->Update();
	currentAnimation2->Update();
	currentAnimation3->Update();

	
	CameraFollowPlayer();

	

	return Update_Status::UPDATE_CONTINUE;
	
}
Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
		SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();

		App->render->Blit(texture, position.x, position.y + 30, &rect2);
		App->render->Blit(texture, position.x, position.y, &rect);
		App->render->Blit(weaponTexture, position.x, position.y, &rect3);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(20, 30, scoreFont, scoreText);

	App->fonts->BlitText(70, 20, scoreFont, "HI");
	App->fonts->BlitText(125, 20, scoreFont, "30000");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider_foot || c1 == collider && destroyed == false&& destroyed==false)
	{
		if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::WALL)
		{
			int to_push_x;
			int to_push_y;
			Collider::ColliderSide side = c1->GetSideToPush(c2->rect, to_push_x, to_push_y);

			LOG("%d", side);

			switch (side)
			{
			case Collider::ColliderSide::UP:
				App->player->position.y += to_push_y;
				break;
			case Collider::ColliderSide::DOWN:
				App->player->position.y += to_push_y;
				break;
			case Collider::ColliderSide::RIGHT:
				App->player->position.x += to_push_x;
				break;
			case Collider::ColliderSide::LEFT:
				App->player->position.x += to_push_x;
				break;
			default:
				break;
			}
		}	

		if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::WATER)
		{
			currentAnimation2 = &trench;
		}

		if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::TRENCH)
		{
			currentAnimation2 = &trench;
		}
		/*if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::CAMERA_UP)
			{
				App->render->camera.y -= 1;
			}
		if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::CAMERA_DOWN)
			{
				App->render->camera.y += 2;
			}
		if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::CAMERA_RIGHT)
			{
				App->render->camera.x += 1;
			}
		if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::CAMERA_LEFT)
			{
				App->render->camera.x -= 2;
			}*/
		//Updated upstream
		if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::WATER)
		{
			currentAnimation2 = &water;
			
			
		}


		
		//Stashed changes
		//Score
		if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
		{
			score += 50;		//Valor placeholder
		}
		
		if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::WATER)
		{	
			
			App->particles->AddParticle(App->particles->dead, position.x, position.y, Collider::Type::NONE, 1);
			

		}
			
		if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::ENEMY)
		{
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 50);

			destroyed = true;
		}

		//Rehén
		if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::HOSTAGE)
		{
			score += 500;
			
		}

		if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::HOSTAGE)
		{
			score -= 500;
		}

		//Collider victoria
		

		//Matar al pj con balas del enemigo
		if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::ENEMY_SHOT)
		{
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 100);
			destroyed = true;
		}
		
		
	}
	
}



void ModulePlayer::CameraFollowPlayer()
{
	int camerax = App->render->GetCameraCenterX();
	int cameray = App->render->GetCameraCenterY();
	
	//Arreglar

	/*int moveCameraUp=cameray-cameraStartFollow;*/
	/*int moveCamera = cameray + cameraStartFollow;
	
	if (position.y <= moveCamera)
	{
		cameray = position.y + cameraStartFollow;
		
	}*/
	
	App->render->SetCameraCenter(position.x-50, position.y-100);

}