#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;


	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

public:
	//Template particle for dead
	Particle dead;

	//Template particle for a bullet
	Particle bullet;	//a la derecha
	Particle bulletL, bulletU, bulletD, bulletUL, bulletUR, bulletDL, bulletDR;
	
	Particle raligunR;
	Particle raligunL, raligunU, raligunD, raligunUL, raligunUR, raligunDL, raligunDR;
	
	Particle enemyBullet;
	Particle enemyBulletU, enemyBulletUR, enemyBulletR, enemyBulletDR, enemyBulletDL, enemyBulletL, enemyBulletUL;
	Particle enemyBulletDLcustom, enemyBulletDRcustom;
	Particle grenade, grenadeExplosion;
	Particle enemygrenade, enemygrenadeExplosion;	

	Particle mas1000, menos500;

	Particle humo;

	//Añadir aqui las diferentes animaciones de muerte
	Particle GreenSoilderDeath, RedSoilderDeath, HostageDeath, HostageCelebrating;

	//Music & FX
	int grenadeExplosionFx;

};

#endif // !__MODULEPARTICLES_H__