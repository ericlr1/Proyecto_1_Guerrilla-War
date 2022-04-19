#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
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
	texture = App->textures->Load("Assets/particles.png");

	// Explosion particle
	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	//Laser right
	laser.anim.PushBack({ 232, 103, 16, 12 });
	laser.anim.PushBack({ 249, 103, 16, 12 });
	laser.speed.x = 5;
	laser.lifetime = 180;
	laser.anim.speed = 0.2f;

	//Laser left
	laserL.anim.PushBack({ 232, 103, 16, 12 });
	laserL.anim.PushBack({ 249, 103, 16, 12 });
	laserL.speed.x = -5;
	laserL.lifetime = 180;
	laserL.anim.speed = 0.2f;

	//Laser up
	laserU.anim.PushBack({ 232, 103, 16, 12 });
	laserU.anim.PushBack({ 249, 103, 16, 12 });
	laserU.speed.y = -5;
	laserU.lifetime = 180;
	laserU.anim.speed = 0.2f;

	//Laser down
	laserD.anim.PushBack({ 232, 103, 16, 12 });
	laserD.anim.PushBack({ 249, 103, 16, 12 });
	laserD.speed.y = 5;
	laserD.lifetime = 180;
	laserD.anim.speed = 0.2f;

	//Laser down-left
	laserDL.anim.PushBack({ 232, 103, 16, 12 });
	laserDL.anim.PushBack({ 249, 103, 16, 12 });
	laserDL.speed.x = -3.5;
	laserDL.speed.y = 3.5;
	laserDL.lifetime = 180;
	laserDL.anim.speed = 0.2f;

	//Laser down-right
	laserDR.anim.PushBack({ 232, 103, 16, 12 });
	laserDR.anim.PushBack({ 249, 103, 16, 12 });
	laserDR.speed.x = 3.5;
	laserDR.speed.y = 3.5;
	laserDR.lifetime = 180;
	laserDR.anim.speed = 0.2f;

	//Laser up-left
	laserUL.anim.PushBack({ 232, 103, 16, 12 });
	laserUL.anim.PushBack({ 249, 103, 16, 12 });
	laserUL.speed.x = -3.5;
	laserUL.speed.y = -3.5;
	laserUL.lifetime = 180;
	laserUL.anim.speed = 0.2f;
	 
	//Laser up-right
	laserUR.anim.PushBack({ 232, 103, 16, 12 });
	laserUR.anim.PushBack({ 249, 103, 16, 12 });
	laserUR.speed.x = 3.5;
	laserUR.speed.y = -3.5;
	laserUR.lifetime = 180;
	laserUR.anim.speed = 0.2f;
	
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
			// TODO 6: Make so every time a particle hits a wall it triggers an explosion particle
			AddParticle(explosion, particles[i]->position.x, particles[i]->position.y);

			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
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

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
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

	return update_status::UPDATE_CONTINUE;
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