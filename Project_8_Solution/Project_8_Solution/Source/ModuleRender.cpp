#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "ModuleCollisions.h"
#include "Collider.h"

#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"


ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled)
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;	
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
Update_Status ModuleRender::PreUpdate()
{
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Clear rendering target
	SDL_RenderClear(renderer);

	

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::Update()
{
	SDL_Point screen_size = GetWindowSize();
	camera.w = screen_size.x;
	camera.h = screen_size.y;
	
	if (camera.y + camera.h > 10490)
	{
		camera.y = 10490 - camera.h;
	}
	//Respawn 1
	if (camera.y + camera.h > 8343 && App->sceneLevel_1->spawn_1 == true)
	{
		camera.y = 8343 - camera.h;
	}
	
	//Respawn 2
   	if (camera.y + camera.h > 6215 && App->sceneLevel_1->spawn_2 ==true)
	{
		camera.y = 6215 - camera.h;
	}
	//Respawn 3
	if (camera.y + camera.h > 4322 && App->sceneLevel_1->spawn_3 == true)
	{
		camera.y = 4322 - camera.h;
	}
	//Respawn 4
	if (camera.y + camera.h > 3247 && App->sceneLevel_1->spawn_4 == true)
	{
		camera.y = 3247 - camera.h;
	}
	//Respawn 5
  	if (camera.y + camera.h > 1742 && App->sceneLevel_1->spawn_5 == true)
	{
		camera.y = 1742 - camera.h;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::PostUpdate()
{
	//Update the screen
	SDL_RenderPresent(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, bool useCamera)
{
	bool ret = true;

	SDL_Rect rect {
		(int)(-camera.x * speed) + x * SCREEN_SIZE,
		(int)(-camera.y * speed) + y * SCREEN_SIZE,
		0, 0 };
	
	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed, bool useCamera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect {
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Point& center, const SDL_Point& size, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed, bool useCamera)
{
	SDL_Rect rect { center.x - (size.x * 0.5), center.y - (size.y * 0.5), size.x , size.y };

	return DrawQuad(rect, r, g, b, a, speed);
}

bool ModuleRender::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed, bool useCamera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	if (SDL_RenderDrawLine(renderer,
		(int)(-camera.x * speed) + x1 * SCREEN_SIZE,
		(int)(-camera.y * speed) + y1 * SCREEN_SIZE,
		(int)(-camera.x * speed) + x2 * SCREEN_SIZE,
		(int)(-camera.y * speed) + y2 * SCREEN_SIZE) != 0) 
	{
		LOG("Cannot draw line to screen. SDL_RenderDrawLine error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

int ModuleRender::GetCameraCenterX()
{
	return (camera.x + (camera.w * 0.5)) / SCREEN_SIZE;
}

int ModuleRender::GetCameraCenterY()
{
	return (camera.y + (camera.h * 0.5)) / SCREEN_SIZE;
}

void ModuleRender::SetCameraCenter(int x, int y)
{
	camera.x = (x * SCREEN_SIZE) - floor(camera.w * 0.5);
	camera.y = (y * SCREEN_SIZE) - floor(camera.h * 0.5);
}

SDL_Point ModuleRender::GetWindowSize()
{
	SDL_Point size;

	SDL_GetWindowSize(App->window->window, &size.x, &size.y);

	return size;
}
