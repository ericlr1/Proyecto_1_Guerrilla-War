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
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	//bullet right
	bullet.anim.PushBack({ 7, 179, 7, 11 });
	bullet.anim.PushBack({ 23, 179, 7, 11 });
	bullet.speed.x = 5;
	bullet.lifetime = 180;
	bullet.anim.speed = 0.2f;


	//bullet left
	bulletL.anim.PushBack({ 232, 103, 16, 12 });
	bulletL.anim.PushBack({ 249, 103, 16, 12 });
	bulletL.speed.x = -5;
	bulletL.lifetime = 180;
	bulletL.anim.speed = 0.2f;

	//bullet up
	bulletU.anim.PushBack({ 7, 179, 7, 11 });
	bulletU.anim.PushBack({23, 179, 7, 11});
	bulletU.speed.y = -5;
	bulletU.lifetime = 180;
	bulletU.anim.speed = 0.2f;

	//bullet down
	bulletD.anim.PushBack({ 232, 103, 16, 12 });
	bulletD.anim.PushBack({ 249, 103, 16, 12 });
	bulletD.speed.y = 5;
	bulletD.lifetime = 180;
	bulletD.anim.speed = 0.2f;

	//bullet down-left
	bulletDL.anim.PushBack({ 232, 103, 16, 12 });
	bulletDL.anim.PushBack({ 249, 103, 16, 12 });
	bulletDL.speed.x = -3.5;
	bulletDL.speed.y = 3.5;
	bulletDL.lifetime = 180;
	bulletDL.anim.speed = 0.2f;

	//bullet down-right
	bulletDR.anim.PushBack({ 232, 103, 16, 12 });
	bulletDR.anim.PushBack({ 249, 103, 16, 12 });
	bulletDR.speed.x = 3.5;
	bulletDR.speed.y = 3.5;
	bulletDR.lifetime = 180;
	bulletDR.anim.speed = 0.2f;

	//bullet up-left
	bulletUL.anim.PushBack({ 232, 103, 16, 12 });
	bulletUL.anim.PushBack({ 249, 103, 16, 12 });
	bulletUL.speed.x = -3.5;
	bulletUL.speed.y = -3.5;
	bulletUL.lifetime = 180;
	bulletUL.anim.speed = 0.2f;

	//bullet up-right
	bulletUR.anim.PushBack({ 232, 103, 16, 12 });
	bulletUR.anim.PushBack({ 249, 103, 16, 12 });
	bulletUR.speed.x = 3.5;
	bulletUR.speed.y = -3.5;
	bulletUR.lifetime = 180;
	bulletUR.anim.speed = 0.2f;

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