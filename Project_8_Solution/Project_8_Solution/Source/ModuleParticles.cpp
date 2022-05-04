#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/particles.png");
	// Explosion particle
	/*dead.anim.PushBack({0, 322, 31, 60});
	dead.anim.PushBack({31, 322, 31, 60});
	dead.anim.PushBack({63, 322, 27, 60});
	dead.anim.PushBack({93, 322, 27, 60});
	dead.anim.PushBack({125, 322, 27, 60});
	dead.anim.PushBack({156, 322, 30, 60});
	dead.anim.PushBack({189, 322, 28, 60});
	dead.anim.PushBack({218, 322, 29, 60});
	dead.anim.PushBack({253, 322, 29, 60});
	dead.anim.PushBack({285, 322, 34, 60});
	
	dead.anim.loop = false;
	dead.anim.speed = 0.1f;*/

	//bullet right
	bullet.anim.PushBack({ 66, 183, 10, 9 });
	bullet.anim.PushBack({ 83, 183, 10, 9 });
	bullet.speed.x = 5;
	bullet.lifetime = 30;
	bullet.anim.speed = 0.2f;


	//bullet left
	bulletL.anim.PushBack({ 196, 182, 9, 9 });
	bulletL.anim.PushBack({ 211, 182, 9, 9 });
	bulletL.speed.x = -5;
	bulletL.lifetime = 30;
	bulletL.anim.speed = 0.2f;

	//bullet up
	bulletU.anim.PushBack({ 7, 179, 7, 11 });
	bulletU.anim.PushBack({23, 179, 7, 11});
	bulletU.speed.y = -5;
	bulletU.lifetime = 30;
	bulletU.anim.speed = 0.2f;

	//bullet down
	bulletD.anim.PushBack({ 133, 178, 8, 13 });
	bulletD.anim.PushBack({ 149, 178, 8, 13 });
	bulletD.speed.y = 5;
	bulletD.lifetime = 30;
	bulletD.anim.speed = 0.2f;

	//bullet down-left
	bulletDL.anim.PushBack({ 165, 180, 8, 12 });
	bulletDL.anim.PushBack({ 181, 180, 8, 12 });
	bulletDL.speed.x = -3.5;
	bulletDL.speed.y = 3.5;
	bulletDL.lifetime = 30;
	bulletDL.anim.speed = 0.2f;

	//bullet down-right
	bulletDR.anim.PushBack({ 98, 180, 9, 12 });
	bulletDR.anim.PushBack({ 114, 180, 9, 12 });
	bulletDR.speed.x = 3.5;
	bulletDR.speed.y = 3.5;
	bulletDR.lifetime = 30;
	bulletDR.anim.speed = 0.2f;

	//bullet up-left
	bulletUL.anim.PushBack({ 228, 181, 8, 11 });
	bulletUL.anim.PushBack({ 244, 181, 8, 11 });
	bulletUL.speed.x = -3.5;
	bulletUL.speed.y = -3.5;
	bulletUL.lifetime = 30;
	bulletUL.anim.speed = 0.2f;

	//bullet up-right
	bulletUR.anim.PushBack({ 35, 181, 9, 11 });
	bulletUR.anim.PushBack({ 51, 181, 9, 11 });
	bulletUR.speed.x = 3.5;
	bulletUR.speed.y = -3.5;
	bulletUR.lifetime = 30;
	bulletUR.anim.speed = 0.2f;


	//Enemy bullet
	enemyBullet.anim.PushBack({ 198, 66, 7, 14 });
	enemyBullet.anim.PushBack({ 215, 66, 7, 14 });
	enemyBullet.speed.y = 5;
	enemyBullet.lifetime = 30;
	enemyBullet.anim.speed = 0.2f;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			//App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}