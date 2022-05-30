#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleDestruibles : public Module
{
public:

	ModuleDestruibles(bool startEnabled);

	~ModuleDestruibles();

	bool Start() override;

	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;


	SDL_Texture* textura_barricada_horizontal = nullptr;
	SDL_Texture* textura_barricada_vertical = nullptr;
	SDL_Texture* textura_espinas = nullptr;

	Collider* barricada_h = nullptr;
	Collider* barricada_v = nullptr;
	Collider* espinas = nullptr;
};