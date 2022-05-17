#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;
	
	

	void CameraFollowPlayer();

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The number related to the orientation of the player
	int facing;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	SDL_Texture* weaponTexture = nullptr;
	SDL_Texture* raligunTexture = nullptr;
	SDL_Texture* palmerasTexture = nullptr;

	

	
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	Animation* currentAnimation2 = nullptr;
	Animation* currentAnimation3 = nullptr;

	// A set of animations
	//Body
	Animation deadAnim, deadfootAnim;											//Muerte Player

	Animation idleupAnim, idleupfootAnim;										//Quieto-Arriba
	Animation idledownAnim, idledownfootAnim;									//Quieto-Abajo
	Animation idlerightAnim, idlerightfootAnim;									//Quieto-Derecha
	Animation idleleftAnim, idleleftfootAnim;									//Quieto-Izquierda

	Animation idlerightupAnim, idlerightupfootAnim;								//Quieto-Derecha-Arriba
	Animation idlerightdownAnim, idlerightdownfootAnim;							//Quieto-Derecha-Abajo
	Animation idleleftupAnim, idleleftupfootAnim;								//Quieto-Izquierda-Arriba
	Animation idleleftdownAnim, idleleftdownfootAnim;							//Quieto-Izquierda-Abajo

	Animation upAnim, upfootAnim;												//Arriba
	Animation downAnim, downfootAnim;											//Abajo
	Animation leftAnim, leftfootAnim;											//Izquierda
	Animation rightAnim, rightfootAnim;											//Derecha
	Animation rightupAnim, rightupfootAnim;										//Derecha-Arriba
	Animation rightdownAnim, rightdownfootAnim;									//Derecha-Abajo
	Animation leftupAnim, leftupfootAnim;										//Izquierda-Arriba
	Animation leftdownAnim, leftdownfootAnim;									//Izquierda-Abajo
	
	//Entorno
	Animation water;															//Agua
	Animation trench;															//Barro
	//Arma
	Animation widleup, widledown, widleleft, widleright;						//Arma-Idle
	Animation widleleftup, widleleftdown, widlerightup, widlerightdown;			//Arma-Idle

	Animation wfireup, wfiredown, wfireleft, wfireright;						//Arma-Fire
	Animation wfireleftup, wfireleftdown, wfirerightup, wfirerightdown;			//Arma-Fire

	Animation raligunidleup, raligunidledown, raligunidleleft, raligunidleright;						//Raligun
	Animation raligunidleleftup, raligunidleleftdown, raligunidlerightup, raligunidlerightdown;

	Animation raligunfireup, raligunfiredown, raligunfireleft, raligunfireright;						//Arma-Fire
	Animation raligunfireleftup, raligunfireleftdown, raligunfirerightup, raligunfirerightdown;

	// The player's collider
	Collider* collider = nullptr;
	Collider* collider_foot = nullptr;
	Collider* collider_camara = nullptr;
	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool water_checker = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 50;

	// Sound effects indices
	uint bulletFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int cameraStartFollow = 35;

	bool raligun = false;


	//Vidas
	int lives = 0;
	char vidas[10] = { "\0" };
	

	//Granadas
	char grenadeNum[10] = { "\0" };
	uint totalGrenades = 50;


	//Coins para jugar
	int coins;
	char monedas[10] = { "\0" };

	//Railgun balas
	char railgunBullets[10] = { "\0" };
	uint ammo_raligun = 0;

	//God mode
	bool godMode = false;
};

#endif //!__MODULE_PLAYER_H_