#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput(bool startEnabled) : Module(startEnabled)
{}

ModuleInput::~ModuleInput()
{}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	num_controllers = SDL_NumJoysticks();
   	for (int i = 0; i < num_controllers; ++i)
		if (SDL_IsGameController(i))
			sdl_controllers[i] = SDL_GameControllerOpen(i);
	 /*Here we don't really have access to the controller
	 SDL_GameController* is obfuscated, it is to know they are there.
	 We will pass data to our own array of controllers*/


	return ret;
}

Update_Status ModuleInput::PreUpdate()
{
	//Read new SDL events, mostly from the window
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return Update_Status::UPDATE_STOP;
	}

	//Read all keyboard data and update our custom array
	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	// Parse Controller button stats
	SDL_GameControllerUpdate();
	for (int i = 0; i < num_controllers; ++i)
	{
		for (int j = 0; j < SDL_CONTROLLER_BUTTON_MAX; ++j)
		{
			if (SDL_GameControllerGetButton(sdl_controllers[i], (SDL_GameControllerButton)j))
				controllers[i].buttons[j] = (controllers[i].buttons[j] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
			else
				controllers[i].buttons[j] = (controllers[i].buttons[j] == KEY_REPEAT || controllers[i].buttons[j] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
		}

		controllers[i].j1_x = SDL_GameControllerGetAxis(sdl_controllers[i], SDL_CONTROLLER_AXIS_LEFTX);
		controllers[i].j1_y = SDL_GameControllerGetAxis(sdl_controllers[i], SDL_CONTROLLER_AXIS_LEFTY);
		controllers[i].j2_x = SDL_GameControllerGetAxis(sdl_controllers[i], SDL_CONTROLLER_AXIS_RIGHTX);
		controllers[i].j2_y = SDL_GameControllerGetAxis(sdl_controllers[i], SDL_CONTROLLER_AXIS_RIGHTY);
		controllers[i].RT = SDL_GameControllerGetAxis(sdl_controllers[i], SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		controllers[i].LT = SDL_GameControllerGetAxis(sdl_controllers[i], SDL_CONTROLLER_AXIS_TRIGGERLEFT);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}