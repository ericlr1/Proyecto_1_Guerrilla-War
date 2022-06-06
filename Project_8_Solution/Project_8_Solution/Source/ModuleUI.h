#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Application.h"
#include "Animation.h"
#include "Module.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:

	ModuleUI(bool isEnabled);

	~ModuleUI();

	//bool Start() override;

	//Update_Status Update() override;

	//Update_Status PostUpdate() override;


	//UI
	SDL_Texture* ui = nullptr;

	//Vidas
	SDL_Texture* iconoVida;

	SDL_Texture* uiTexture = nullptr;

	SDL_Texture* iconoRailgun = nullptr;

	SDL_Texture* limites = nullptr;

	int num;

};



#endif //!__MODULE_UI_H__


