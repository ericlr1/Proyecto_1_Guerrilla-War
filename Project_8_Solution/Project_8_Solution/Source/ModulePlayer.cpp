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
#include "SceneLevel1.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "ModuleDestruibles.h"


#include "SDL/include/SDL_scancode.h"

#include <stdio.h>
#include <SDL/include/SDL_timer.h>
#include <SDL/include/SDL_video.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//Invisible
	invisibleAnim.PushBack({-32, 0, 32, 32});

	invisibleUpAnim.PushBack({-32, 0, 32, 32});

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

	idlewater.PushBack({ 192,256,32,32 });
	
	//trench

	trench.PushBack({ 160,256,32,32 });
	trench.PushBack({ 160,288,32,32 });
	trench.PushBack({ 160,288,32,32 });

	trench.loop = true;
	trench.speed = 0.1f;
	trench.pingpong = false;

	idletrench.PushBack({ 160,256,32,32 });
		
	// -UP-	[x]
	//Idle
	widleup.PushBack({ -4, 19, 32, 32 });
	widleup.loop = false;
	widleup.speed = 0.f;
	widleup.pingpong = false;
	//Fire
	wfireup.PushBack({ -4, 137, 32, 32 });
	wfireup.loop = false;
	wfireup.speed = 0.2f;
	wfireup.pingpong = false;

	// -RIGHT/UP-	[x]
	//Idle
	widlerightup.PushBack({ 52, 19, 32, 32 });
	widlerightup.loop = false;
	widlerightup.speed = 0.2f;
	widlerightup.pingpong = false;
	//Fire
	wfirerightup.PushBack({ 52, 140, 38, 32 });
	wfirerightup.loop = false;
	wfirerightup.speed = 0.2f;
	wfirerightup.pingpong = false;
	
	// -RIGHT-	[x]
	//Idle
	widleright.PushBack({ 106, 12, 32, 39 });
	widleright.loop = false;
	widleright.speed = 0.2f;
	widleright.pingpong = false;
	//Fire
	wfireright.PushBack({ 108, 132, 38, 39 });
	wfireright.loop = false;
	wfireright.speed = 0.2f;
	wfireright.pingpong = false;
	
	// -RIGHT/DOWN-	[x]
	//Idle
	widlerightdown.PushBack({ 188, 12, 32, 39 });
	widlerightdown.loop = false;
	widlerightdown.speed = 0.2f;
	widlerightdown.pingpong = false;
	//Fire
	wfirerightdown.PushBack({ 188, 124, 34, 48 });
	wfirerightdown.loop = false;
	wfirerightdown.speed = 0.2f;
	wfirerightdown.pingpong = false;
	
	// -DOWN-	[x]
	//Idle
	widledown.PushBack({ 265, 10, 32, 41 });
	widledown.loop = false;
	widledown.speed = 0.2f;
	widledown.pingpong = false;
	//Fire
	wfiredown.PushBack({ 267, 120, 32, 50 });
	wfiredown.loop = false;
	wfiredown.speed = 0.2f;
	wfiredown.pingpong = false;
	
	// -LEFT/DOWN-	[x]
	//Idle
	widleleftdown.PushBack({ 343, 7, 32, 39 });
	widleleftdown.loop = false;
	widleleftdown.speed = 0.2f;
	widleleftdown.pingpong = false;
	//Fire
	wfireleftdown.PushBack({ 338, 132 , 41, 44 });
	wfireleftdown.loop = false;
	wfireleftdown.speed = 0.2f;
	wfireleftdown.pingpong = false;
	
	// -LEFT-	[x]
	//Idle
	widleleft.PushBack({ 403, 12, 36, 34 });
	widleleft.loop = false;
	widleleft.speed = 0.2f;
	widleleft.pingpong = false;
	//Fire
	wfireleft.PushBack({ 398, 135, 54, 32 });
	wfireleft.loop = false;
	wfireleft.speed = 0.2f;
	wfireleft.pingpong = false;
	
	// -LEFT/UP-	[X]
	//Idle
	widleleftup.PushBack({ 483, 19, 29, 32 });
	widleleftup.loop = false;
	widleleftup.speed = 0.2f;
	widleleftup.pingpong = false;
	//Fire
	wfireleftup.PushBack({ 483, 140, 29, 32 });
	wfireleftup.loop = false;
	wfireleftup.speed = 0.2f;
	wfireleftup.pingpong = false;
	


	// -UP-	[x]
		//Ralligun
		//Idle
	raligunidleup.PushBack({ -4, 274, 25, 29 });
	raligunidleup.loop = false;
	raligunidleup.speed = 0.2f;
	raligunidleup.pingpong = false;

	//Fire
	raligunfireup.PushBack({ -4, 137, 32, 32 });
	raligunfireup.loop = false;
	raligunfireup.speed = 0.2f;
	raligunfireup.pingpong = false;

	
	// -RIGHT/UP-	[x]
	// Ralligun
	//Idle
	raligunidlerightup.PushBack({ 48, 274, 38, 32 });
	raligunidlerightup.loop = false;
	raligunidlerightup.speed = 0.2f;
	raligunidlerightup.pingpong = false;
	//Fire
	raligunfirerightup.PushBack({ 46, 397, 44, 32 });
	raligunfirerightup.loop = false;
	raligunfirerightup.speed = 0.2f;
	raligunfirerightup.pingpong = false;

	// -RIGHT-	[x]
	// Ralligun
	//Idle
	raligunidleright.PushBack({ 106, 257, 39, 36 });
	raligunidleright.loop = false;
	raligunidleright.speed = 0.2f;
	raligunidleright.pingpong = false;
	//Fire
	raligunfireright.PushBack({ 103, 387, 45, 37 });
	raligunfireright.loop = false;
	raligunfireright.speed = 0.2f;
	raligunfireright.pingpong = false;

	// -RIGHT/DOWN-	[x]
	// Ralligun
	//Idle
	raligunidlerightdown.PushBack({ 187, 250, 32, 45 });
	raligunidlerightdown.loop = false;
	raligunidlerightdown.speed = 0.2f;
	raligunidlerightdown.pingpong = false;
	//Fire
	raligunfirerightdown.PushBack({ 188, 380, 39, 51 });
	raligunfirerightdown.loop = false;
	raligunfirerightdown.speed = 0.2f;
	raligunfirerightdown.pingpong = false;

	// -DOWN-	[x]
	// Ralligun
	//Idle
	raligunidledown.PushBack({ 265, 250, 32, 45 });
	raligunidledown.loop = false;
	raligunidledown.speed = 0.2f;
	raligunidledown.pingpong = false;
	//Fire
	raligunfiredown.PushBack({ 262, 378, 33, 54 });
	raligunfiredown.loop = false;
	raligunfiredown.speed = 0.2f;
	raligunfiredown.pingpong = false;

	// -LEFT/DOWN-	[x]
	// Ralligun
	//Idle
	raligunidleleftdown.PushBack({ 338, 249, 33, 39 });
	raligunidleleftdown.loop = false;
	raligunidleleftdown.speed = 0.2f;
	raligunidleleftdown.pingpong = false;
	//Fire
	raligunfireleftdown.PushBack({ 337, 390, 32, 42 });
	raligunfireleftdown.loop = false;
	raligunfireleftdown.speed = 0.2f;
	raligunfireleftdown.pingpong = false;

	// -LEFT-	[x]
	// Ralligun
	//Idle
	raligunidleleft.PushBack({ 401, 250, 32, 32 });
	raligunidleleft.loop = false;
	raligunidleleft.speed = 0.2f;
	raligunidleleft.pingpong = false;
	//Fire
	raligunfireleft.PushBack({ 399, 390, 32, 32 });
	raligunfireleft.loop = false;
	raligunfireleft.speed = 0.2f;
	raligunfireleft.pingpong = false;

	// -LEFT/UP-	[X]
	// 
	// Ralligun
	//Idle
	raligunidleleftup.PushBack({ 480, 256, 32, 32 });
	raligunidleleftup.loop = false;
	raligunidleleftup.speed = 0.2f;
	raligunidleleftup.pingpong = false;
	//Fire

	raligunfireleftup.PushBack({ 480, 394, 32, 32 });
	raligunfireleftup.loop = false;
	raligunfireleftup.speed = 0.2f;
	raligunfireleftup.pingpong = false;

	//GRENADE
	// Throw grenade animations
	upThrowGrenade.PushBack({ 320, 0, 32, 32 });
	upThrowGrenade.PushBack({ 352, 0, 32, 32 });
	upThrowGrenade.PushBack({ 384, 0, 32, 32 });
	upThrowGrenade.PushBack({ 416, 0, 32, 32 });
	upThrowGrenade.PushBack({ 448, 0, 32, 32 });
	upThrowGrenade.speed = 0.1f;
	upThrowGrenade.loop = false;

	upRightThrowGrenade.PushBack({ 320, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 352, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 384, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 416, 32, 32, 32 });
	upRightThrowGrenade.PushBack({ 448, 32, 32, 32 });
	upRightThrowGrenade.speed = 0.1f;
	upRightThrowGrenade.loop = false;

	rightThrowGrenade.PushBack({ 320, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 352, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 384, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 416, 64, 32, 32 });
	rightThrowGrenade.PushBack({ 448, 64, 32, 32 });
	rightThrowGrenade.speed = 0.1f;
	rightThrowGrenade.loop = false;

	downRightThrowGrenade.PushBack({ 320, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 352, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 384, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 416, 96, 32, 32 });
	downRightThrowGrenade.PushBack({ 448, 96, 32, 32 });
	downRightThrowGrenade.speed = 0.1f;
	downRightThrowGrenade.loop = false;

	downThrowGrenade.PushBack({ 320, 128, 32, 32 });
	downThrowGrenade.PushBack({ 352, 128, 32, 32 });
	downThrowGrenade.PushBack({ 384, 128, 32, 32 });
	downThrowGrenade.PushBack({ 416, 128, 32, 32 });
	downThrowGrenade.PushBack({ 448, 128, 32, 32 });
	downThrowGrenade.speed = 0.1f;
	downThrowGrenade.loop = false;

	downLeftThrowGrenade.PushBack({ 320, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 352, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 384, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 416, 160, 32, 32 });
	downLeftThrowGrenade.PushBack({ 448, 160, 32, 32 });
	downLeftThrowGrenade.speed = 0.1f;
	downLeftThrowGrenade.loop = false;

	leftThrowGrenade.PushBack({ 320, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 352, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 384, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 416, 192, 32, 32 });
	leftThrowGrenade.PushBack({ 448, 192, 32, 32 });
	leftThrowGrenade.speed = 0.1f;
	leftThrowGrenade.loop = false;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	App->UI->iconoVida = App->textures->Load("Assets/Sprites/UI _Vidas.png"); //Icono vida
	palmerasTexture= App->textures->Load("Assets/Sprites/Palmeras.png");
	raligunTexture = App->textures->Load("Assets/Sprites/raligun.png");
	texture = App->textures->Load("Assets/Sprites/Characters_Clean.png"); // arcade version
	weaponTexture = App->textures->Load("Assets/Sprites/weapon.png");
	App->UI->uiTexture = App->textures->Load("Assets/Sprites/granadaUI.png"); //Granada UI
	App->UI->iconoRailgun = App->textures->Load("Assets/Sprites/pistolaUI.png"); //Raligun
	App->UI->limites = App->textures->Load("Assets/Sprites/limites.png");
	
	// Initiate player audios here
	shotFx = App->audio->LoadFx("Assets/Fx/142.wav"); // shot sfx
	playerDeadFx = App->audio->LoadFx("Assets/Fx/195.wav"); // dead sfx
	heavyRifleFx = App->audio->LoadFx("Assets/Fx/153.wav");
	throwGrenadeFx = App->audio->LoadFx("Assets/Fx/137.wav");
	weaponPickUpFx = App->audio->LoadFx("Assets/Fx/165.wav");
	
	//Spawn point
	spawnPoint = -INT_MAX;
	t1 = SDL_GetTicks();
	continueCooldown = 9;
	deathCooldown = 0;
	invincibleCooldown = 0;

	//UI 

	//Reset de la score
	score = 0;

	//Reset de las vidas
	lives = 3;


	coins = 1;

	//Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUV."};
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
		currentAnimation3 = &widleleftdown;
		currentAnimation2 = &idleleftdownfootAnim;
		currentAnimation = &idleleftdownAnim;
		
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
	collider_camara =App->collisions->AddCollider({0,0, 485, 16 }, Collider::Type::WALL);
	return ret;
}

float reduce_val(bool controllerON, float v1, float min, float clamp_to) {
	if (controllerON)
	{
		float sign = v1 / fabs(v1);
		float reduced = v1 - ((fabs(v1) > min) ? sign * min : v1);
		float to_1 = reduced / (float)(SDL_MAX_SINT16);
		float reclamped = to_1 * clamp_to;
		return reclamped;
	}
	else
	{
		return 0;
	}
}

Update_Status ModulePlayer::Update()    
{
	float fx = 0, fy = 0;

	fx += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2);
	fy += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2);
	fx += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j2_x, 10000, 2);
	fy += reduce_val(SDL_IsGameController(0), App->input->controllers[0].j2_y, 10000, 2);

	// GAMEPAD: Triggers Count as axis, have specific values
	if (App->input->controllers[0].LT > SDL_MAX_SINT16 / 2) {
		fx *= 2;
		fy *= 2;
	}
	if (App->input->controllers[0].RT > SDL_MAX_SINT16 / 2) {
		fx *= 3;
		fy *= 3;
	}

	// GAMEPAD: Fire with any button for now to check they all work
	bool button_press = false;
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (App->input->controllers[0].buttons[i] == KEY_DOWN)
		{
			button_press = true; break;
		}
	}


	// Moving the player with the camera scroll
	//App->player->position.y += 1;
	
	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN)
	{
		facing = 0;
	}
	
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
	{
		return Update_Status::UPDATE_STOP;
	}

	//Coins
	if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_Y] == Key_State::KEY_DOWN)
	{
		if (coins == 3)
		{

		}
		else
		{
			coins += 1;
			lives += 3;
		}

	}

	if (App->input->keys[SDL_SCANCODE_U] == Key_State::KEY_DOWN)
	{
		ammo_raligun += 10;
	}

	if (freeCam == true)
	{


		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			App->render->camera.y += 7;
		}

		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{
			App->render->camera.x -= 7;
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			App->render->camera.x += 7;
		}

		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			App->render->camera.y -= 7;
		}

	}

	//Auto win
	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN)
	{
	
		destroyed = true;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 30);
	}

	//Auto kill
	if (App->input->keys[SDL_SCANCODE_J] == Key_State::KEY_DOWN)
	{

		lives = 0;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 60);
		destroyed = true;
	}

	//Auto win //Creo que está mal
	if (App->input->keys[SDL_SCANCODE_L] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 100);
		destroyed = true;
	}

	//Granada
	if (App->input->keys[SDL_SCANCODE_LALT] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == Key_State::KEY_DOWN)
	{
		if (totalGrenades == 0)
		{

		}
		else
		{
			throwGrenade();
			//totalGrenades--;
			//App->particles->AddParticle(App->particles->grenade, position.x + 20, position.y, Collider::Type::NONE);
			////Añadir particula explosion con collider
			//
			//App->particles->AddParticle(App->particles->grenadeExplosion, position.x-7, position.y-110, Collider::Type::PLAYER_SHOT);
			//App->audio->PlayFx(bulletFx);
			//currentAnimation3 = &wfireup;
			
		}
		
	}

	

	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN)
	{
		lives++;
	}

	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN)
	{
		lives--;
	}
	
	if (App->input->keys[SDL_SCANCODE_F] == Key_State::KEY_DOWN)
	{
		freeCam = !freeCam;
		godMode = !godMode;

	}

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_X] == Key_State::KEY_DOWN)
	{
		
		if (godMode == false)
		{
			speed += 3;
		}
		else
		{
			speed -= 3;
		}
		godMode = !godMode;
	}

	if (App->input->keys[SDL_SCANCODE_T] == Key_State::KEY_DOWN)
	{
		shortcuts = !shortcuts;
	}

	//Spawning enemies menu
	if (shortcuts == true)
	{
		if (App->input->keys[SDL_SCANCODE_F9] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_F10] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::TRIPLESHOT, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::REDSOLDIER, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_F8] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::GREENSOLDIER2, position.x, position.y - 100);		//Tackler
		}

		if (App->input->keys[SDL_SCANCODE_H] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::HOSTAGE, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN)
		{
			App->enemies->AddEnemy(Enemy_Type::GRENADER, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN)
		{
			App->destruibles->AddDestruible(Destruible_Type::BARRICADA_H, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN)
		{
			App->destruibles->AddDestruible(Destruible_Type::BARRICADA_V, position.x, position.y - 100);
		}

		if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN)
		{
			App->destruibles->AddDestruible(Destruible_Type::ESPINAS, position.x, position.y - 100);
		}
	}
	
	// If the player is dead
	if (dead == true) {
		godMode = true;

		deathCooldown++;
		if (deathCooldown == 0) {
			App->audio->PlayFx(playerDeadFx);
		}

		
		if (deathCooldown >= DEATH_ANIM_DURATION) {

			if (lives == 0) {


				int t2 = SDL_GetTicks();
				if ((t2 - t1) / 1000.0f >= 1) {
					continueCooldown--;
					t1 = t2;
				}

				if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || button_press) {
					lives = 3;
					continueCooldown = 9;
				}

				if (continueCooldown == 0)
				{
					App->player->CleanUp();
					App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 0);
				
				}
					

			}
			else {

				facing = 0;

				dead = false;
				totalGrenades = 50;

				spawnPoint = this->position.y;
				this->position.y += 150;
				
				ammo_raligun = 0;

				immovable = true;
			}
		}
	}

	// Invincible frames
	if (lives != 0) {
		if (deathCooldown >= DEATH_ANIM_DURATION) {
			invincibleCooldown++;
			if (spawnPoint < this->position.y) {
				this->position.y--;
			}
			if (invincibleCooldown >= INVINCIBLE_DURATION) {
				godMode = false;
				deathCooldown = 0;
				invincibleCooldown = 0;
			}
		}
		else {
			immovable = false;
		}
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && dead == false && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) < 0 && dead == false && immovable == false)
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
			if(walk_water==true){ currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }

			break;
		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;
		}
	}
	

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && dead == false && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) > 0 && dead == false && immovable == false)
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
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && dead == false && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) > 0 && dead == false && immovable == false)
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
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && dead == false && immovable == false
		|| reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) < 0 && dead == false && immovable == false)
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
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 1:
			if (currentAnimation != &rightupAnim && currentAnimation2 != &rightupfootAnim)
			{
				rightupAnim.Reset();
				rightupfootAnim.Reset();
				currentAnimation = &rightupAnim;
				currentAnimation2 = &rightupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 2:
			if (currentAnimation != &rightAnim && currentAnimation2 != &rightfootAnim)
			{
				rightAnim.Reset();
				rightfootAnim.Reset();
				currentAnimation = &rightAnim;
				currentAnimation2 = &rightfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 3:
			if (currentAnimation != &rightdownAnim && currentAnimation2 != &rightdownfootAnim)
			{
				rightdownAnim.Reset();
				rightdownfootAnim.Reset();
				currentAnimation = &rightdownAnim;
				currentAnimation2 = &rightdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 4:
			if (currentAnimation != &downAnim && currentAnimation2 != &downfootAnim)
			{
				downAnim.Reset();
				downfootAnim.Reset();
				currentAnimation = &downAnim;
				currentAnimation2 = &downfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 5:
			if (currentAnimation != &leftdownAnim && currentAnimation2 != &leftdownfootAnim)
			{
				leftdownAnim.Reset();
				leftdownfootAnim.Reset();
				currentAnimation = &leftdownAnim;
				currentAnimation2 = &leftdownfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 6:
			if (currentAnimation != &leftAnim && currentAnimation2 != &leftfootAnim)
			{
				leftAnim.Reset();
				leftfootAnim.Reset();
				currentAnimation = &leftAnim;
				currentAnimation2 = &leftfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;

		case 7:
			if (currentAnimation != &leftupAnim && currentAnimation2 != &leftupfootAnim)
			{
				leftupAnim.Reset();
				leftupfootAnim.Reset();
				currentAnimation = &leftupAnim;
				currentAnimation2 = &leftupfootAnim;
			}if (walk_water == true) { currentAnimation2 = &water; }
			if (walk_trench == true) { currentAnimation2 = &trench; }
			break;
		}

	}

	//Rotación del personaje Q y E
	if (App->input->keys[SDL_SCANCODE_E] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] == Key_State::KEY_DOWN)
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

	if (App->input->keys[SDL_SCANCODE_Q] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] == Key_State::KEY_DOWN)
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
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_B] == Key_State::KEY_DOWN)
	{
		//La variable facing aumenta al rotar hacia la derecha (Como las agujas del reloj)
		if (ammo_raligun > 0)
		{
			switch (facing)
			{
			case 0:
				App->particles->AddParticle(App->particles->raligunU, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfireup;
				break;

			case 1:
				App->particles->AddParticle(App->particles->raligunUR, position.x + 18, position.y + 8, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfirerightup;
				break;

			case 2:
				App->particles->AddParticle(App->particles->raligunR, position.x + 20, position.y + 27, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfireright;
				break;

			case 3:
				App->particles->AddParticle(App->particles->raligunDR, position.x + 12, position.y + 30, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfirerightdown;
				break;

			case 4:
				App->particles->AddParticle(App->particles->raligunD, position.x + 10, position.y + 40, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfiredown;
				break;

			case 5:
				App->particles->AddParticle(App->particles->raligunDL, position.x-10 , position.y +20, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfireleftdown;
				break;

			case 6:
				App->particles->AddParticle(App->particles->raligunL, position.x -10, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfireleft;
				break;

			case 7:
				App->particles->AddParticle(App->particles->raligunUL, position.x -3, position.y, Collider::Type::PLAYER_SHOT);
				App->audio->PlayFx(heavyRifleFx);
				currentAnimation3 = &raligunfireleftup;
				break;
			}
			ammo_raligun -= 1;
		}
		else
		{
			switch (facing)
			{
			case 0:
				App->particles->AddParticle(App->particles->bulletU, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 20, position.y - 100, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfireup;
				break;

			case 1:
				App->particles->AddParticle(App->particles->bulletUR, position.x + 20, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 20 + 100, position.y - 100 + 20, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfirerightup;
				break;

			case 2:
				App->particles->AddParticle(App->particles->bullet, position.x + 20, position.y + 25, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 20 + 100, position.y + 25, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfireright;
				break;

			case 3:
				App->particles->AddParticle(App->particles->bulletDR, position.x + 12, position.y + 30, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 12 + 100, position.y + 100 + 30, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfirerightdown;
				break;

			case 4:
				App->particles->AddParticle(App->particles->bulletD, position.x + 10, position.y + 25, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 10, position.y + 100 + 25, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfiredown;
				break;

			case 5:
				App->particles->AddParticle(App->particles->bulletDL, position.x + 10, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 10 - 100, position.y + 100 + 20, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfireleftdown;
				break;

			case 6:
				App->particles->AddParticle(App->particles->bulletL, position.x + 5, position.y + 20, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 5 - 100, position.y + 20, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfireleft;
				break;

			case 7:
				App->particles->AddParticle(App->particles->bulletUL, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
				App->particles->AddParticle(App->particles->humo, position.x + 5 - 100, position.y - 100 + 15, Collider::Type::NONE);
				App->audio->PlayFx(shotFx);
				currentAnimation3 = &wfireleftup;
				break;
			}
			
		}
	}


	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&& reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_x, 10000, 2) == 0
		&& reduce_val(SDL_IsGameController(0), App->input->controllers[0].j1_y, 10000, 2) == 0)
	{
		if (walk_trench == true)
		{
			switch (facing)
			{
			case 0:
				currentAnimation = &idleupAnim;
				currentAnimation2 = &idletrench;
				break;

			case 1:
				currentAnimation = &idlerightupAnim;
				currentAnimation2 = &idletrench;
				break;

			case 2:
				currentAnimation = &idlerightAnim;
				currentAnimation2 = &idletrench;
				break;

			case 3:
				currentAnimation = &idlerightdownAnim;
				currentAnimation2 = &idletrench;
				break;

			case 4:
				currentAnimation = &idledownAnim;
				currentAnimation2 = &idletrench;
				break;

			case 5:
				currentAnimation = &idleleftdownAnim;
				currentAnimation2 = &idletrench;
				break;

			case 6:
				currentAnimation = &idleleftAnim;
				currentAnimation2 = &idletrench;
				break;

			case 7:
				currentAnimation = &idleleftupAnim;
				currentAnimation2 = &idletrench;
				break;
			}

		}
		if (walk_water == true)
		{
			switch (facing)
			{
			case 0:
				currentAnimation = &idleupAnim;
				currentAnimation2 = &idlewater;
				break;

			case 1:
				currentAnimation = &idlerightupAnim;
				currentAnimation2 = &idlewater;
				break;

			case 2:
				currentAnimation = &idlerightAnim;
				currentAnimation2 = &idlewater;
				break;

			case 3:
				currentAnimation = &idlerightdownAnim;
				currentAnimation2 = &idlewater;
				break;

			case 4:
				currentAnimation = &idledownAnim;
				currentAnimation2 = &idlewater;
				break;

			case 5:
				currentAnimation = &idleleftdownAnim;
				currentAnimation2 = &idlewater;
				break;

			case 6:
				currentAnimation = &idleleftAnim;
				currentAnimation2 = &idlewater;
				break;

			case 7:
				currentAnimation = &idleleftupAnim;
				currentAnimation2 = &idlewater;
				break;
			}
		}
			if (walk_water == false && walk_trench == false)
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
			}
		
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_IDLE || button_press)
	{
		if (ammo_raligun > 0)
		{
			switch (facing)
			{
			case 0:
				currentAnimation3 = &raligunfireup;
				currentAnimation3 = &raligunidleup;
				break;

			case 1:
				currentAnimation3 = &raligunfirerightup;
				currentAnimation3 = &raligunidlerightup;
				break;

			case 2:

				currentAnimation3 = &raligunfireright;
				currentAnimation3 = &raligunidleright;
				break;

			case 3:
				currentAnimation3 = &raligunfirerightdown;
				currentAnimation3 = &raligunidlerightdown;
				break;

			case 4:
				currentAnimation3 = &raligunfiredown;
				currentAnimation3 = &raligunidledown;
				break;

			case 5:
				currentAnimation3 = &raligunfireleftdown;
				currentAnimation3 = &raligunidleleftdown;
				break;

			case 6:
				currentAnimation3 = &raligunfireleft;
				currentAnimation3 = &raligunidleleft;
				break;

			case 7:
				currentAnimation3 = &raligunfireleftup;
				currentAnimation3 = &raligunidleleftup;
				break;
			}
		}

		else
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
	collider_camara->SetPos(App->render->GetCameraCenterX()-100, App->render->GetCameraCenterY() +160);

	////Fade si vidas < 0
	//if (lives == 0)
	//{
	//	App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 60);
	//	destroyed = true;
	//}


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
		SDL_Rect rect;
		SDL_Rect rect2; 
		SDL_Rect rect3; 

		if (dead == false)
		{
			rect = currentAnimation->GetCurrentFrame();
			rect2 = currentAnimation2->GetCurrentFrame();
			rect3 = currentAnimation3->GetCurrentFrame();
		}
		else
		{
			rect = invisibleAnim.GetCurrentFrame();
			rect2 = invisibleAnim.GetCurrentFrame();
			rect3 = invisibleAnim.GetCurrentFrame();
		}
		

		if (ammo_raligun <= 0)
		{
			App->render->Blit(raligunTexture, 214, 3106, NULL, 1.0, false);
		}
		App->render->Blit(texture, position.x, position.y + 30, &rect2);
		App->render->Blit(weaponTexture, position.x, position.y, &rect3);
		App->render->Blit(texture, position.x, position.y, &rect);
	
		

		App->render->Blit(palmerasTexture, 0, 0, NULL, 1.0, false);

		//UI
		App->render->Blit(App->UI->uiTexture, App->render->GetCameraCenterX() - 100, App->render->GetCameraCenterY() - 110, NULL, 1.0, false);
		for (int i = 0; i < lives; i++)
		{

			App->render->Blit(App->UI->iconoVida,  App->render->GetCameraCenterX() - 100  + (9 * i), App->render->GetCameraCenterY() + 120, NULL, 1.0, false);
		}
		App->render->Blit(App->UI->limites, App->render->GetCameraCenterX()-450, App->render->GetCameraCenterY()-200, NULL, 1.0, false);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%5d", score);
	sprintf_s(grenadeNum, 10, "%d", totalGrenades);
	sprintf_s(vidas, 10, "%d", lives);
	sprintf_s(monedas, 10, "%d", coins);
	sprintf_s(railgunBullets, 10, "%d", ammo_raligun);
	sprintf_s(continueTimer, 10, "%d", continueCooldown);

	if (lives == 0)
	{
		//Continue screen
		App->fonts->BlitText(SCREEN_WIDTH / 2+120, SCREEN_HEIGHT / 2, scoreFont, continueTimer);
		App->fonts->BlitText(SCREEN_WIDTH / 2+115, (SCREEN_HEIGHT / 2 )- 10, scoreFont, "CONTINUE.IN");
		App->fonts->BlitText(SCREEN_WIDTH / 2+133, SCREEN_HEIGHT / 2, scoreFont, "SECONDS");
	}
	

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText((SCREEN_WIDTH / 2)+93 , (SCREEN_HEIGHT / 2)-115, scoreFont, scoreText);

	App->fonts->BlitText((SCREEN_WIDTH / 2) + 110, (SCREEN_HEIGHT / 2) - 140, scoreFont, "HI");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 150, (SCREEN_HEIGHT / 2 - 140), scoreFont, "30000");
	App->fonts->BlitText((SCREEN_WIDTH / 2) + 70, (SCREEN_HEIGHT / 2) - 125, scoreFont, "1..UP");

	App->fonts->BlitText(220, 87  , scoreFont, grenadeNum);

	if (ammo_raligun > 0)
	{
		App->render->Blit(App->UI->iconoRailgun, App->render->GetCameraCenterX() - 100 , App->render->GetCameraCenterY() - 82, NULL, 1.0, true);
		App->fonts->BlitText((SCREEN_WIDTH / 2)+58 , (SCREEN_HEIGHT / 2)-47 ,scoreFont, railgunBullets);
	}

	if (App->collisions->debug == true)
	{
		App->fonts->BlitText(10, 5, scoreFont, vidas);
		if (godMode == true)
		{
			App->fonts->BlitText(10, 300, scoreFont, "GODMODE.ON");
		}
		else
		{
			App->fonts->BlitText(10, 300, scoreFont, "GODMODE.OFF");
		}

		if (shortcuts == false)
		{
			App->fonts->BlitText(10, 180, scoreFont, "PRESS.T.FOR.SHORTCUTS");
		}

		if (shortcuts == true)
		{
			App->fonts->BlitText(10, 180, scoreFont, "F8.TACKLER");		//Green Soilder 2
			App->fonts->BlitText(10, 190, scoreFont, "F10.TRIPLESHOT");
			App->fonts->BlitText(10, 200, scoreFont, "F11.RED.SOILDER");
			App->fonts->BlitText(10, 210, scoreFont, "F9.GREEN.SOILDER");	
			App->fonts->BlitText(10, 220, scoreFont, "H.HOSTAGE");
			App->fonts->BlitText(10, 230, scoreFont, "G.GRENADER");
			App->fonts->BlitText(10, 240, scoreFont, "B.REGULAR.BARICADE");
			App->fonts->BlitText(10, 250, scoreFont, "N.ROTATED.BARICADE");
			App->fonts->BlitText(10, 260, scoreFont, "M.SPIKES");
		}

		App->fonts->BlitText(10, 290, scoreFont, "COINS");
		App->fonts->BlitText(50, 290, scoreFont, monedas);


		if (freeCam == false)
		{
			int camerax = App->render->GetCameraCenterX();
			int cameray = App->render->GetCameraCenterY();

			App->render->DrawQuad({ camerax, cameray }, { 10, 10 }, 255, 0, 0, 255);

			int moveCameraUp = cameray - cameraStartFollow;
			int moveCameraDown = cameray + cameraStartFollow;
			int moveCameraRight = camerax + cameraStartFollow;
			int moveCameraLeft = camerax - cameraStartFollow;

			App->render->DrawQuad({ camerax, moveCameraUp }, { 10, 5 }, 255, 255, 0, 255);
			App->render->DrawQuad({ camerax, moveCameraDown }, { 10, 5 }, 255, 0, 255, 255);
			App->render->DrawQuad({ moveCameraRight, cameray }, { 5, 10 }, 255, 255, 0, 255);
			App->render->DrawQuad({ moveCameraLeft, cameray }, { 5, 10 }, 255, 0, 255, 255);
		}
	}
	

	//App->fonts->BlitText(70, 50, scoreFont, totalGrenades);

	return Update_Status::UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (destroyed)
	{
		return;
	}

	if (c1 != collider_foot && c1 != collider)
	{
		return;
	}

	bool isNonWalkable = c1->type == Collider::Type::FOOT && 
		(c2->type == Collider::Type::WALL || c2->type == Collider::Type::DESTRUIBLE);

	if (isNonWalkable)
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
		walk_water = true;
		switch (facing)
		{
		case 0:
			currentAnimation2 = &water;
			break;

		case 1:
			currentAnimation2 = &water;
			break;

		case 2:;
			currentAnimation2 = &water;
			break;

		case 3:
			currentAnimation2 = &water;
			break;

		case 4:
			currentAnimation2 = &water;
			break;

		case 5:
			currentAnimation2 = &water;
			break;

		case 6:
			currentAnimation2 = &water;
			break;

		case 7:
			currentAnimation2 = &water;
			break;
		}
	}
	else {
		walk_water = false;
	}
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::TRENCH)
	{
		walk_trench = true;
		switch (facing)
		{
		case 0:
			currentAnimation2 = &trench;
			break;

		case 1:
			currentAnimation2 = &trench;
			break;

		case 2:;
			currentAnimation2 = &trench;
			break;

		case 3:
			currentAnimation2 = &trench;
			break;

		case 4:
			currentAnimation2 = &trench;
			break;

		case 5:
			currentAnimation2 = &trench;
			break;

		case 6:
			currentAnimation2 = &trench;
			break;

		case 7:
			currentAnimation2 = &trench;
			break;
		}
	}
	else
	{
		walk_trench = false;
	}
	
	if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::EXPLOSION)
	{
		if (godMode == false)
		{
			this->dead = true;
			this->immovable = true;
			currentAnimation = &invisibleAnim;
			currentAnimation2 = &invisibleUpAnim;
			lives--;
			App->particles->AddParticle(App->particles->dead, position.x, position.y, Collider::Type::NONE);
			if (lives == 3 || lives == 6)
			{
				coins--;
			}
		}

	}

	if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::ENEMY)
	{
		if (godMode == false)
		{
			this->dead = true;
			this->immovable = true;
			currentAnimation = &invisibleAnim;
			currentAnimation2 = &invisibleUpAnim;
			lives--;
			App->particles->AddParticle(App->particles->dead, position.x, position.y, Collider::Type::NONE);
			if (lives == 3 || lives == 6)
			{
				coins--;
			}
		}

	}

	//Matar al pj con balas del enemigo
	if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::ENEMY_SHOT)
	{
		if (godMode == false)
		{
			this->dead = true;
			this->immovable = true;
			currentAnimation = &invisibleAnim;
			currentAnimation2 = &invisibleUpAnim;
			lives--;
			App->particles->AddParticle(App->particles->dead, position.x, position.y, Collider::Type::NONE);
			if (lives == 3 || lives == 6)
			{
				coins--;
			}
		}
	}

	
	if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::RALIGUN)
	{
		App->audio->PlayFx(weaponPickUpFx);
		ammo_raligun = 50;
	}


	if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::RALIGUN)
	{
		App->sceneLevel_1->raligun_colldier->pendingToDelete = true;


		switch (facing)
		{
		case 0:
			currentAnimation3 = &raligunidleup;
			break;

		case 1:
			currentAnimation3 = &raligunidlerightup;
			break;

		case 2:;
			currentAnimation3 = &raligunidleright;
			break;

		case 3:
			currentAnimation3 = &raligunidlerightdown;
			break;

		case 4:
			currentAnimation3 = &raligunidledown;
			break;

		case 5:
			currentAnimation3 = &raligunidleleftdown;
			break;

		case 6:
			currentAnimation3 = &raligunidleleft;
			break;

		case 7:
			currentAnimation3 = &raligunidleleftup;
			break;

		}
	}
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESET_ANIM_WATER)
	{
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
		{
			switch (facing)
			{
			case 0:
				currentAnimation2 = &upfootAnim;
				break;

			case 1:
				currentAnimation2 = &rightupfootAnim;
				break;
			case 2:
				currentAnimation2 = &rightfootAnim;
				break;
			case 3:
				currentAnimation2 = &rightdownfootAnim;
				break;
			case 4:
				currentAnimation2 = &downfootAnim;
				break;
			case 5:
				currentAnimation2 = &leftdownfootAnim;
				break;
			case 6:
				currentAnimation2 = &leftfootAnim;
				break;
			case 7:
				currentAnimation2 = &leftupfootAnim;
				break;
			}
		}

	}
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESET_ANIM_TRENCH)
	{
		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT
			|| App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT
			)
		{
			switch (facing)
			{
			case 0:
				currentAnimation2 = &upfootAnim;
				break;

			case 1:
				currentAnimation2 = &rightupfootAnim;
				break;
			case 2:
				currentAnimation2 = &rightfootAnim;
				break;
			case 3:
				currentAnimation2 = &rightdownfootAnim;
				break;
			case 4:
				currentAnimation2 = &downfootAnim;
				break;
			case 5:
				currentAnimation2 = &leftdownfootAnim;
				break;
			case 6:
				currentAnimation2 = &leftfootAnim;
				break;
			case 7:
				currentAnimation2 = &leftupfootAnim;
				break;
			}
		}
	}
	//Spawns
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESPAWN_1)
	{
		App->sceneLevel_1->spawn_1 = true;
	}
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESPAWN_2)
	{
		App->sceneLevel_1->spawn_2 = true;
	}
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESPAWN_3)
	{
		App->sceneLevel_1->spawn_3 = true;
	}
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESPAWN_4)
	{
		App->sceneLevel_1->spawn_4 = true;
	}
	if (c1->type == Collider::Type::FOOT && c2->type == Collider::Type::RESPAWN_5)
	{
		App->sceneLevel_1->spawn_5 = true;
	}

	if (c1->type == Collider::Type::BODY && c2->type == Collider::Type::WIN)
	{
		
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLose, 60);
		destroyed = true;
	}
}



void ModulePlayer::CameraFollowPlayer()
{
	if (freeCam == false)
	{
		int camerax = App->render->GetCameraCenterX();
		int cameray = App->render->GetCameraCenterY();

		int moveCameraUp = cameray - cameraStartFollow;
		int moveCameraDown = cameray + cameraStartFollow;
		int moveCameraRight = camerax + cameraStartFollow;
		int moveCameraLeft = camerax - cameraStartFollow;

		if (position.y <= moveCameraUp)
		{
			cameray = position.y + cameraStartFollow;
		}

		if (position.y >= moveCameraDown - 64)
		{
			cameray = position.y - cameraStartFollow + 64;

		}

		if (position.x >= moveCameraRight - 32)
		{
			camerax = position.x - cameraStartFollow + 32;

		}

		if (position.x <= moveCameraLeft)
		{
			camerax = position.x + cameraStartFollow;

		}

		App->render->SetCameraCenter(camerax, cameray);
	}
}


void ModulePlayer::throwGrenade() {
	
	totalGrenades--;
	App->audio->PlayFx(throwGrenadeFx);
	//App->particles->grenade.explodes = true;
	switch (facing) {
	case 0:
		App->particles->grenade.speed.x = 0;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x + 13, position.y, Collider::Type::NONE);
		break;
	case 1:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x + 10 , position.y + 10, Collider::Type::NONE);
		break;
	case 2:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = 0;
		App->particles->AddParticle(App->particles->grenade, position.x + 10, position.y + 5, Collider::Type::NONE);
		break;
	case 3:
		App->particles->grenade.speed.x = 2;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x + 10, position.y + 10, Collider::Type::NONE);
		break;
	case 4:
		App->particles->grenade.speed.x = 0;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x + 10, position.y + 50, Collider::Type::NONE);
		break;
	case 5:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = 2;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y + 10, Collider::Type::NONE);
		break;
	case 6:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = 0;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y + 10, Collider::Type::NONE);
		break;
	case 7:
		App->particles->grenade.speed.x = -2;
		App->particles->grenade.speed.y = -2;
		App->particles->AddParticle(App->particles->grenade, position.x, position.y, Collider::Type::NONE);
		break;
	}

}

bool ModulePlayer::CleanUp() {
	//App->fonts->Disable();
	App->textures->Unload(texture);
	App->textures->Unload(weaponTexture);
	App->audio->UnloadFx(shotFx);
	App->audio->UnloadFx(playerDeadFx);
	App->audio->UnloadFx(heavyRifleFx);
	App->audio->UnloadFx(throwGrenadeFx);
	App->fonts->UnLoad(scoreFont);
	return true;
}
