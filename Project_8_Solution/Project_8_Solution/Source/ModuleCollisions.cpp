#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

#include "ModulePlayer.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::BODY] = false;
	matrix[Collider::Type::WALL][Collider::Type::FOOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::WATER] = false;
	matrix[Collider::Type::WALL][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::WALL][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::WALL][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::WALL][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::WALL][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::WALL][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::WALL][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::WALL][Collider::Type::WIN] = false;
	matrix[Collider::Type::WALL][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::WALL][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::WALL][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::WALL][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::WALL][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::BODY][Collider::Type::WALL] = false;
	matrix[Collider::Type::BODY][Collider::Type::BODY] = false;
	matrix[Collider::Type::BODY][Collider::Type::FOOT] = false;
	matrix[Collider::Type::BODY][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BODY][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BODY][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::BODY][Collider::Type::WATER] = false;
	matrix[Collider::Type::BODY][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::BODY][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::BODY][Collider::Type::RALIGUN] = true;
	matrix[Collider::Type::BODY][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::BODY][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::BODY][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::BODY][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::BODY][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::BODY][Collider::Type::WIN] = true;
	matrix[Collider::Type::BODY][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::BODY][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::BODY][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::BODY][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::BODY][Collider::Type::RESPAWN_5] = false;
	

	matrix[Collider::Type::FOOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::FOOT][Collider::Type::BODY] = false;
	matrix[Collider::Type::FOOT][Collider::Type::FOOT] = false;
	matrix[Collider::Type::FOOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::FOOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::FOOT][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::FOOT][Collider::Type::WATER] = true;
	matrix[Collider::Type::FOOT][Collider::Type::TRENCH] = true;
	matrix[Collider::Type::FOOT][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RALIGUN] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::FOOT][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::FOOT][Collider::Type::DESTRUIBLE] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RESET_ANIM_TRENCH] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RESET_ANIM_WATER] = true;
	matrix[Collider::Type::FOOT][Collider::Type::WIN] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RESPAWN_1] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RESPAWN_2] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RESPAWN_3] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RESPAWN_4] = true;
	matrix[Collider::Type::FOOT][Collider::Type::RESPAWN_5] = true;
	

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BODY] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::FOOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WATER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RALIGUN_SHOOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::DESTRUIBLE] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WIN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::RESPAWN_5] = false;
	
	
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BODY] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::FOOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WIN] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::RESPAWN_5] = false;
	
	
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BODY] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::FOOT] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::DESTRUIBLE] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WIN] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::WATER][Collider::Type::WALL] = false;
	matrix[Collider::Type::WATER][Collider::Type::BODY] = false;
	matrix[Collider::Type::WATER][Collider::Type::FOOT] = true;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::WATER] = false;
	matrix[Collider::Type::WATER][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::WATER][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::WATER][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::WATER][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::WATER][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::WATER][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::WATER][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::WATER][Collider::Type::WIN] = false;
	matrix[Collider::Type::WATER][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::WATER][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::WATER][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::WATER][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::WATER][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::TRENCH][Collider::Type::WALL] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::BODY] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::FOOT] = true;
	matrix[Collider::Type::TRENCH][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::TRENCH][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::WATER] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::WIN] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::TRENCH][Collider::Type::RESPAWN_5] = false;

	
	matrix[Collider::Type::HOSTAGE][Collider::Type::WALL] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::BODY] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::WATER] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RALIGUN_SHOOT] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::HOSTAGE][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::WIN] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESPAWN_5] = false;

	
	matrix[Collider::Type::RALIGUN][Collider::Type::WALL] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::BODY] = true;
	matrix[Collider::Type::RALIGUN][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RALIGUN][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::RALIGUN][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::WATER] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::WIN] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RALIGUN][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::HOSTAGE][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::BODY] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::FOOT] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::DESTRUIBLE] = true;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::WIN] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RALIGUN_SHOOT][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::EXPLOSION][Collider::Type::WALL] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::BODY] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::FOOT] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::WATER] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::HOSTAGE] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RALIGUN_SHOOT] = true;
	matrix[Collider::Type::EXPLOSION][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::DESTRUIBLE] = true;	
	matrix[Collider::Type::EXPLOSION][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::WIN] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::EXPLOSION][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::DESTRUIBLE][Collider::Type::WALL] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::BODY] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::FOOT] = true;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::WATER] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RALIGUN_SHOOT] = true;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::EXPLOSION] = true;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::WIN] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::DESTRUIBLE][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::WALL] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::BODY] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::WATER] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::WIN] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RESET_ANIM_WATER][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::WALL] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::BODY] = true;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::WATER] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::WIN] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RESET_ANIM_TRENCH][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::WIN][Collider::Type::WALL] = false;
	matrix[Collider::Type::WIN][Collider::Type::BODY] = true;
	matrix[Collider::Type::WIN][Collider::Type::FOOT] = true;
	matrix[Collider::Type::WIN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WIN][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WIN][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WIN][Collider::Type::WATER] = false;
	matrix[Collider::Type::WIN][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::WIN][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::WIN][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::WIN][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::WIN][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::WIN][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::WIN][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::WIN][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::WIN][Collider::Type::WIN] = false;
	matrix[Collider::Type::WIN][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::WIN][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::WIN][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::WIN][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::WIN][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RESPAWN_1][Collider::Type::WALL] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::BODY] = true;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::WATER] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::WIN] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RESPAWN_1][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RESPAWN_2][Collider::Type::WALL] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::BODY] = true;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::WATER] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::WIN] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RESPAWN_2][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RESPAWN_3][Collider::Type::WALL] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::BODY] = true;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::WATER] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::WIN] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RESPAWN_3][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RESPAWN_4][Collider::Type::WALL] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::BODY] = true;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::WATER] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::WIN] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RESPAWN_4][Collider::Type::RESPAWN_5] = false;


	matrix[Collider::Type::RESPAWN_5][Collider::Type::WALL] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::BODY] = true;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::FOOT] = true;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::WATER] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::TRENCH] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::HOSTAGE] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RALIGUN] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RALIGUN_SHOOT] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::EXPLOSION] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::DESTRUIBLE] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RESET_ANIM_TRENCH] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RESET_ANIM_WATER] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::WIN] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RESPAWN_1] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RESPAWN_2] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RESPAWN_3] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RESPAWN_4] = false;
	matrix[Collider::Type::RESPAWN_5][Collider::Type::RESPAWN_5] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->Intersects(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->listener) 
					c1->listener->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->listener) 
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN || App->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == Key_State::KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			
			case Collider::Type::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			
			case Collider::Type::BODY: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			
			case Collider::Type::FOOT: // Dark yellow
			App->render->DrawQuad(colliders[i]->rect, 256, 150, 0, alpha);
			break;
			
			case Collider::Type::WATER: //Blue
			App->render->DrawQuad(colliders[i]->rect, 111, 232, 231, alpha);
			break;
			
			case Collider::Type::TRENCH: //Blue
			App->render->DrawQuad(colliders[i]->rect, 123, 0, 255, alpha);
			break;
			
			case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			
			case Collider::Type::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			
			case Collider::Type::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			
			case Collider::Type::RALIGUN: // Gray
			App->render->DrawQuad(colliders[i]->rect, 150, 150, 150, alpha);
			break;
			
			case Collider::Type::RALIGUN_SHOOT: // Blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;

			case Collider::Type::HOSTAGE: // Lime
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 20, alpha);
			break;

			case Collider::Type::WIN: // Lime
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 100, alpha);
			break;

			case Collider::Type::DESTRUIBLE: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

			case Collider::Type::RESPAWN_1: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

			case Collider::Type::RESPAWN_2: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

			case Collider::Type::RESPAWN_3: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

			case Collider::Type::RESPAWN_4: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

			case Collider::Type::RESPAWN_5: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

			case Collider::Type::EXPLOSION: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 50, alpha);
			break;
		
			case Collider::Type::RESET_ANIM_WATER: // Lime
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

			case Collider::Type::RESET_ANIM_TRENCH: // Lime
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}



